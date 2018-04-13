bin_PROGRAMS =	exe1

exe1_SOURCES = 	Main.cpp\
				Factory.cpp	\
				ProductionScheduling.cpp	\
				ProductionControl.cpp\
				ProductionControl_test.cpp\
				LoadConfiguration.cpp	\
				Buffer.cpp\
				../Exe2/Machine.cpp\
				../Exe2/ProxyProductionControl.cpp\
				LocalMachine.cpp\
				LocalMachine_test.cpp\
				ProxyMachine.cpp \
				ProxyClock.cpp \
				../Exe2/Machine_test.cpp\
				../Exe2/MachineCalculations.cpp\
				../Exe2/ConcreteState.cpp\
				../Exe2/Events.cpp\
				../Exe2/Clock.cpp\
				../Exe2/AbstractState.cpp \
				Logger/Log_to_console.cpp\
				Logger/Log_to_file.cpp\
				Logger/Queue.cpp\
				Logger/Queued_logger.cpp\
				Logger/Queued_logger_test.cpp\
				Network/CommunicationService.cpp\
				Network/controlNetworkHandler.cpp\
				Network/machineNetworkHandler.cpp

exe1_CPPFLAGS =	$(AM_CPPFLAGS) $(PROJECTTEMPLATE_CPPFLAGS) $(WX_CPPFLAGS)	\
				-DPROJECTTEMPLATEEXE=1	\
				-I $(top_srcdir)/Config

exe1_CFLAGS = 	$(AM_CFLAGS) $(PROJECTTEMPLATE_CFLAGS) $(WX_CFLAGS)

exe1_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTTEMPLATE_CXXFLAGS) $(BOOST_CPPFLAGS) $(WX_CXXFLAGS)

exe1_LDFLAGS = 	$(AM_LDFLAGS) $(PROJECTTEMPLATE_LDFLAGS) $(BOOST_LDFLAGS) $(WX_LDFLAGS)

exe1_LDADD =	$(BOOST_LIBS)	\
				$(SOCKET_LIBS)	\
				$(WX_LIBS)
