#include "CController.h"

#include "CModel.h"
#include "CAction.h"
#include "CEnvironment.h"
#include "Matrix/Matrix.hpp"
#include <random>

namespace
{
    constexpr const int ROBOT_MAX_POS_X = 1024;
	constexpr const int ROBOT_MAX_POS_Y = 1024;
	constexpr const int ROBOT_MIN_POS_X = 0;
	constexpr const int ROBOT_MIN_POS_Y = 0;

	constexpr const float ROBOTWORLD_MAX_WIDTH = 1024.0;
}

CController::CController(Model::Robot* pRobot)
: m_spModel(std::make_shared<CModel>(pRobot))
, m_spEnvironment(std::make_shared<CEnvironment>(pRobot))
, m_particleBelief(0, 0)
, m_pRobot(pRobot)
{
}

CController::~CController()
{
    delete m_pRobot;
}

void CController::ParticleFilter(std::vector<float> rRobotLidarValues, Widgets::Point& rMovement)
{
    std::vector<float> nIterWeights;
    std::vector<CParticle> tempParticles;

    // Step one:
    // Move every particle with the same movement included with a standard deviation.
    // Scan the environment with a Lidar Sensor and store them into a vector.
    for(int i = 0; i < m_particleVector.size(); ++i)
    {
        int stdDev = CalcMovementStdDeviation();
        m_particleVector[i].DoMovement(rMovement.x + stdDev, rMovement.y + stdDev);
        m_particleVector[i].SetMeasurements(m_pRobot->ActivateLidarBeam(Widgets::Point(m_particleVector[i].GetX(), m_particleVector[i].GetY())));
    }

    // Step two:
    // Compare every particle with the position of the Robot.
    float weightTotalForLottery = 0.0;
    float meanWeight = 0.0;
    float min = 1.0;
    float max = 0.0;
    for(auto& aParticle : m_particleVector)
    {
        float total = 0.0;

        for(int i = 0; i < rRobotLidarValues.size(); ++i)
        {
            total += (1.0 - (fabs(aParticle.GetMeasurements()[i] - rRobotLidarValues[i]) / ROBOTWORLD_MAX_WIDTH));
        }

        meanWeight = total / rRobotLidarValues.size();
        aParticle.SetWeight(meanWeight);

        //Calc minimal and maximum
        if(aParticle.GetWeight() > max)
        {
            max = aParticle.GetWeight() + 0.01;
        }
        else if(aParticle.GetWeight() < min)
        {
            min = aParticle.GetWeight() - 0.01;
        }
    }

    // Mapping the minimum and maximum into a wider
    // spectrum from 0 to 1.0 to make the differences bigger.
    for(auto& aParticle : m_particleVector)
    {
        float dc = (1.0) / (max - min);
        float mappedWeight = dc * (aParticle.GetWeight() - min);
        aParticle.SetWeight(mappedWeight);
        nIterWeights.push_back(mappedWeight);
        weightTotalForLottery += mappedWeight;
    }

    // Step three:
    // Create a weighted lottery based on particels to generate a new belief
    static std::random_device random{};
    static std::mt19937 randomGenerator(random());
    std::uniform_int_distribution<std::mt19937::result_type> randomDist
    {
        0, weightTotalForLottery
    };

    double randomLottery;
    float endOfRange = 0.0;
    for(int i = 0; i < m_particleVector.size(); ++i)
    {
        randomLottery = randomDist(randomGenerator);
        for(int j = 0; j < m_particleVector.size(); ++j)
        {
            endOfRange += nIterWeights[j];
            if(randomLottery <= endOfRange)
            {
                tempParticles.push_back(m_particleVector[j]);
                endOfRange = 0.0;
                break;
            }
        }
    }
    assert(m_particleVector.size() == tempParticles.size());
    m_particleVector = tempParticles;
    
    // Step Four:
    // Get the particle which has the highest occurance
    uint64_t highestOccurance = 0;
    for(const auto& aParticle : m_particleVector)
    {
        uint64_t count = std::count(m_particleVector.begin(), m_particleVector.end(), aParticle);

        if(count >= highestOccurance)
        {
            highestOccurance = count;
            m_particleBelief = aParticle;
        }
    }
}

int CController::CalcMovementStdDeviation()
{
    std::random_device random{};
    std::mt19937 randomGenerator(random());
    std::normal_distribution<float> odomNoise{0.0, 1.0};
    int returnValue = static_cast<int>(odomNoise(randomGenerator));

    return returnValue;
}


void CController::GenerateRandomParticles(int nParticles)
{
	for(int i = 0; i < nParticles; ++i)
	{
		std::random_device random{};
		std::mt19937 randomGenerator(random());
		std::uniform_int_distribution<int> X{ROBOT_MIN_POS_X, ROBOT_MAX_POS_X};
		std::uniform_int_distribution<int> Y{ROBOT_MIN_POS_Y, ROBOT_MAX_POS_Y};
		m_particleVector.push_back(CParticle(X(randomGenerator), Y(randomGenerator)));
	}
}

void CController::KalmanFilter(CAction aAction, CMeasurement aMeasurement)
{
    // Step one
    Matrix<TYPE, STATES, 1> meanPredict = (m_spEnvironment->getAt() * m_spModel->GetMean())
                                                    + (aAction.GetBt() * aAction.GetUt());

    // Step two
    Matrix<TYPE, STATES, STATES> varPredict = (m_spEnvironment->getAt() * m_spModel->GetVariance())
                                             * m_spEnvironment->getAt().transpose() + (m_spEnvironment->GetEt()
                                             * m_spEnvironment->GetEt().transpose());
    
    // Step three
    Matrix<TYPE, STATES, MEASUREMENTS> kalmanGain = varPredict * aMeasurement.GetCt().transpose() *
                                             ((aMeasurement.GetCt() * varPredict * aMeasurement.GetCt().transpose() +
                                              aMeasurement.GetDt() * aMeasurement.GetDt().transpose()).inverse());

    // Step four
    m_spModel->SetMean(meanPredict + kalmanGain * (aMeasurement.GetZt() - (aMeasurement.GetCt() * meanPredict)));
    m_spModel->SetVariance((varPredict.identity() - (kalmanGain * aMeasurement.GetCt())) * varPredict);

    // Testing Kalman Train                         
    //std::cout << "Mean: " << m_spModel->GetMean().to_string() << std::endl;
    //std::cout << "Variance: " << m_spModel->GetVariance().to_string() << std::endl;
}

std::shared_ptr<CModel> CController::GetModel() const
{
    return m_spModel;
}

std::shared_ptr<CEnvironment> CController::GetEnvironment() const
{
    return m_spEnvironment;
}

CParticle& CController::GetParticleBelief()
{
    return m_particleBelief;
}