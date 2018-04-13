bin_PROGRAMS =	exe2

exe2_SOURCES = 	Main.cpp \
		Clock.cpp \
		ConcreteState.cpp \
		Events.cpp \
		ProxyProductionControl.cpp \
		Machine.cpp \
		MachineCalculations.cpp \
		Machine_test.cpp \
		AbstractState.cpp \
		../Exe1/Network/CommunicationService.cpp \
		../Exe1/Network/controlNetworkHandler.cpp \
		../Exe1/Network/machineNetworkHandler.cpp \
		../Exe1/Logger/Log_to_console.cpp \
		../Exe1/Logger/Log_to_file.cpp \
		../Exe1/Logger/Queue.cpp \
		../Exe1/Logger/Queued_logger.cpp \
		../Exe1/ProductionControl.cpp \
		../Exe1/LocalMachine.cpp\
		../Exe1/ProxyMachine.cpp \
		../Exe1/ProxyClock.cpp \
		../Exe1/LoadConfiguration.cpp	\
		../Exe1/Buffer.cpp 
				
exe2_CPPFLAGS =	$(AM_CPPFLAGS) $(PROJECTTEMPLATE_CPPFLAGS) $(WX_CPPFLAGS)	\
				-DPROJECTTEMPLATEEXE=1	\
				-I $(top_srcdir)/Config
exe2_CFLAGS = 	$(AM_CFLAGS) $(PROJECTTEMPLATE_CFLAGS) $(WX_CFLAGS)

exe2_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTTEMPLATE_CXXFLAGS) $(BOOST_CPPFLAGS) $(WX_CXXFLAGS)

exe2_LDFLAGS = 	$(AM_LDFLAGS) $(PROJECTTEMPLATE_LDFLAGS) $(BOOST_LDFLAGS) $(WX_LDFLAGS)

exe2_LDADD =	$(BOOST_LIBS)	\
				$(SOCKET_LIBS)	\
				$(WX_LIBS)
