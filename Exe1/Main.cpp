#include "Defines.hpp" // <!--set debug/test variables in this file

#include <iostream>

#if UNITTEST > 0
#define BOOST_TEST_MODULE Queued_logger_test_module
#define BOOST_TEST_MODULE SimulatorTest
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#endif

#include "Logger/Queued_logger.hpp"
#include "Logger/Log_to_file.hpp"
#include "ProductionControl.hpp"
#include "Network/machineNetworkHandler.hpp"
#include "Factory.hpp"

int main(int argc, char* argv[])
{
#if UNITTEST > 0
	return boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
#endif
	try
	{
		std::cout << "\t\t !- productiestraat-spaanders -! " << std::endl;

		Queued_logger::get_instance().switch_logger_type(
				new Log_to_file("result.csv"));
		Queued_logger::get_instance().log(""); //TODO: logt af en toe naar terminal en af en toe naar file...
		Queued_logger::get_instance().log(
				"SIM_DAY,TIME_OF_DAY (H:M),MACHINE/BUFFER,ID,MACHINE_NAME,STATE,CURRENT_MACHINE_AMOUNT_OF_WORK,MILLISECONDS_FROM_SIM_START");

		//Factory implementatie
		Factory f;
		f.startSimulation("../../Exe1/master.ini");

		while (FactoryClock::getInstance()->isRunning())
		{

		}
		std::this_thread::sleep_for (std::chrono::milliseconds(1000)); // TODO: zorgt ervoor dat statistics zijn weggeschreven

		Queued_logger::get_instance().stop();

		std::cout << "Application End." << std::endl;
		return 0;
	} catch (std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	} catch (...)
	{
		std::cout << "Unknown exception caught." << std::endl;
	}
	return -1;
}
