bin_PROGRAMS = robotworld
robotworld_SOURCES 	= 	AbstractActuator.cpp	\
						AbstractAgent.cpp	\
						AbstractSensor.cpp	\
						AStar.cpp	\
						BoundedVector.cpp	\
						CommunicationService.cpp	\
						DebugTraceFunction.cpp	\
						Goal.cpp	\
						GoalShape.cpp	\
						LaserDistanceSensor.cpp	\
						LineShape.cpp	\
						Logger.cpp	\
						LogTextCtrl.cpp	\
						Main.cpp	\
						MainApplication.cpp	\
						MainFrameWindow.cpp	\
						MathUtils.cpp	\
						ModelObject.cpp	\
						NotificationHandler.cpp	\
						Notifier.cpp	\
						ObjectId.cpp	\
						Observer.cpp	\
						RectangleShape.cpp	\
						Robot.cpp	\
						RobotShape.cpp	\
						RobotWorld.cpp	\
						RobotWorldCanvas.cpp	\
						Shape2DUtils.cpp	\
						StdOutDebugTraceFunction.cpp	\
						SteeringActuator.cpp	\
						ViewObject.cpp	\
						Wall.cpp	\
						WallShape.cpp	\
						WayPoint.cpp	\
						WayPointShape.cpp	\
						WidgetDebugTraceFunction.cpp	\
						BP/CAction.cpp \
						BP/CController.cpp \
						BP/CEnvironment.cpp \
						BP/CMeasurement.cpp \
						BP/CModel.cpp \
						BP/CParticle.cpp \
						BP/Matrix/Matrix.inc \
						Widgets.cpp
									
robotworld_CPPFLAGS 	=	$(AM_CPPFLAGS) $(ROBOTWORLD_CPPFLAGS) $(WX_CPPFLAGS)

robotworld_CFLAGS 		=   $(AM_CFLAGS)   $(ROBOTWORLD_CFLAGS)	  $(WX_CFLAGS)

robotworld_CXXFLAGS 	=	$(BOOST_CPPFLAGS) $(WX_CXXFLAGS)

robotworld_LDFLAGS 		= 	$(AM_LDFLAGS)  $(ROBOTWORLD_LDFLAGS)  $(BOOST_LDFLAGS) $(WX_LDFLAGS)

robotworld_LDADD 		= 	$(AM_LIBADD)   $(WX_LIBS)   $(BOOST_LIBS) $(SOCKET_LIBS)
