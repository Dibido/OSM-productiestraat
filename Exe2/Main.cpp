#include "Defines.hpp" // <!--set debug/test variables in this file

#include <iostream>

#include "../Exe1/Logger/Queued_logger.hpp"
#include "../Exe1/ProductionControl.hpp"
#include "../Exe1/Network/controlNetworkHandler.hpp"
#include "../Exe1/IniParser/IniParser.hpp"
#include "MachineState.hpp"
#include "ProxyProductionControl.hpp"

using namespace std;

int main()
{
	IniParser::getInstance().setFile("../../Exe2/configMachineNetwork.ini");
	ControlNetworkHandlerPtr cnhPtr = std::make_shared<controlNetworkHandler>(nullptr);
	ProxyProductionControl ppc(nullptr, cnhPtr);
	ProxyProductionControl* ppcPtr = &ppc;
	cnhPtr->setProxyProductionControlPtr(ppcPtr);
	cnhPtr->startCommunicating();
	getchar();
	return 0;
}
