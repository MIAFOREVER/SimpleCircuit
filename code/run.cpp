#include<iostream>
using namespace std;
#include"Gate.cpp"
#include"HighGui.cpp"
class run
{
#define MAXGATE 100
private:
	Gate * store[MAXGATE];
	int num;
public:
	run()
	{
		for (int i = 0; i < MAXGATE; i++)
			store[i] = NULL;
		num = 0;
	}
	~run()
	{
		clear();
	}
	int createPort()
	{
		Gate* gate = new Port();
		gate->setId(num);
		store[num] = gate;
		num++;
		return num - 1;
	}
	int createNotGate()
	{
		Gate* gate = new NotGate(); 
		gate->setId(num);
		store[num] = gate;
		num++;
		return num - 1;
	}
	int createXorGate()
	{
		Gate* gate = new XorGate();
		gate->setId(num);
		store[num] = gate;
		num++;
		return num - 1;
	}
	int createAndGate()
	{
		Gate* gate = new AndGate();
		gate->setId(num);
		store[num] = gate;
		num++;
		return num - 1;
	}
	int createOrGate()
	{
		Gate* gate = new OrGate();
		gate->setId(num);
		store[num] = gate;
		num++;
		return num - 1;
	}
	void runMainProgram()
	{
		for (int j = 0; j < num; j++)
		{
			for (int i = 0; i < 100; i++)
			{
				if (store[i] != NULL)
					store[i]->run();
			}
		}
	}
	void display()
	{
		cout << "We have four states: \n-1 is unknown \n1  is high \n0  is low \n-2 is short circuit!\n";
		for (int i = 0; i < 100; i++)
		{
			if (store[i] != NULL)
			{
				if (store[i]->name() != "Port")
				{
					cout << "id: " << i << "\t" << "property: " << store[i]->name();
					cout << "\tinput_0: " << store[i]->getNode()->input[0];
					cout << "\tinput_1: " << store[i]->getNode()->input[1];
					cout << "\toutput: " << store[i]->getNode()->output;
					cout << endl;
					cout << "\t\t\t\t|\t\t|\t\t|\n";
					if (store[i]->getNode()->prev[0] != NULL)
						cout << "\t\t\t\t" << store[i]->getNode()->prev[0]->nodeId;
					else
						cout << "\t\t\t\tNULL";
					if (store[i]->getNode()->prev[1] != NULL)
						cout << "\t\t" << store[i]->getNode()->prev[1]->nodeId<<"\t\t";
					else
						cout << "\t\tNULL\t\t";
					bool temp = true;
					for (int j = 0; j < 20; j++)
					{
						if (store[i]->getNode()->next[j]!=NULL)
						{
							if (store[i]->getNode()->next[j]->prev[0] == store[i]->getNode())
								cout << store[i]->getNode()->next[j]->nodeId << " ->input_0 ";
							if (store[i]->getNode()->next[j]->prev[1] == store[i]->getNode())
								cout << store[i]->getNode()->next[j]->nodeId << " ->input_1 ";
							temp = false;
						}
					}
					if (temp)
					{
						cout << "NULL";
					}
					cout << endl;
				}
				else
				{
					cout << "id: " << i << "\t" << "property: " << store[i]->name();
					cout << "\t\tinput: " << store[i]->getNode()->input[0];
					cout << "\toutput: " << store[i]->getNode()->output;
					cout << endl;
					cout << "\t\t\t\t|\t\t|\n";
					if (store[i]->getNode()->prev[0] == NULL)
						cout << "\t\t\t\tNULL\t\t";
					if (store[i]->getNode()->prev[0] != NULL)
						cout << "\t\t\t\t" << store[i]->getNode()->prev[0]->nodeId<<"\t\t";
					bool temp = true;
					for (int j = 0; j < 20; j++)
					{
						if (store[i]->getNode()->next[j] != NULL)
						{
							if (store[i]->getNode()->next[j]->prev[0] == store[i]->getNode())
								cout << store[i]->getNode()->next[j]->nodeId << " ->input_0 ";
							if (store[i]->getNode()->next[j]->prev[1] == store[i]->getNode())
								cout << store[i]->getNode()->next[j]->nodeId << " ->input_1 ";
							temp = false;
						}
					}
					if (temp)
					{
						cout << "NULL";
					}
					cout << endl;
				}
			}
		}
	}
	void connect(int srcNum, int dstNum, int dstPort)
	{
		Gate* srcGate = store[srcNum];
		Gate* dstGate = store[dstNum];
		srcGate->connect(dstGate, dstPort);
	}
	void disconnect(int srcNum, int dstNum, int dstPort)
	{
		Gate* srcGate = store[srcNum];
		Gate* dstGate = store[dstNum];
		srcGate->disconnect(dstGate, dstPort);
	}
	void setPort(int srcNum, int state)
	{
		Gate* srcGate = store[srcNum];
		srcGate->setPortState(state);
	}
	void clear()
	{
		if (num != 0)
		{
			for (int i = 0; i < num; i++)
			{
				delete store[i];
			}
			for (int i = 0; i < MAXGATE; i++)
				store[i] = NULL;
			num = 0;
		}
	}
	void clean()
	{
		if (num != 0)
		{
			for (int i = 0; i < num; i++)
			{
				Gate* temp = store[i];
				temp->getNode()->input[0] = -1;
				temp->getNode()->input[1] = -1;
				temp->getNode()->output = -1;
			}
		}
	}
	void main()
	{
		HighGui gui;
		gui.firstPage();
		char choice;
		cin >> choice;	
		while (choice<'1'&&choice>'9')
		{
			cout << "Please write the right number you want choice.\n";
			cin >> choice;
		}
		while (choice != '9')
		{
			if (choice == '1')
			{
				gui.clear();
				b:
				gui.gateCreatePage();
				char gateType;
				cin >> gateType;
				if (gateType == '5')
				{
					int gateNum = createPort();
					Gate* temp = store[gateNum];
					cout << "Remember the " << temp->name() << " id : " << gateNum << endl;
				}
				else if (gateType == '1')
				{
					int gateNum = createAndGate();
					Gate* temp = store[gateNum];
					cout << "Remember the " << temp->name() << " id : " << gateNum << endl;
				}
				else if (gateType == '2')
				{
					int gateNum = createOrGate();
					Gate* temp = store[gateNum];
					cout << "Remember the " << temp->name() << " id : " << gateNum << endl;
				}
				else if (gateType == '3')
				{
					int gateNum = createNotGate();
					Gate* temp = store[gateNum];
					cout << "Remember the " << temp->name() << " id : " << gateNum << endl;
				}
				else if (gateType == '4')
				{
					int gateNum = createXorGate();
					Gate* temp = store[gateNum];
					cout << "Remember the " << temp->name() << " id : " << gateNum << endl;
				}
				else
				{
					cout << "Please write the right gate type name.\n";
					goto b;
				}
				gui.clear();
			}
			if (choice == '2')
			{
				display();
				if (num < 2)
				{
					cout << "Please create two gates first!\n";
					cout << "Please type anything to continue!\n";
					char systemPause;
					cin >> systemPause;

				}
				else
				{
					gui.gateConnectPage();
					int srcGateNum, dstGateNum, dstPortNum;
					cin >> srcGateNum >> dstGateNum >> dstPortNum;
					while (srcGateNum == dstGateNum)
					{
						cout << "The two gates must be separate gates !\n";
						cout << "Please type again!\n";
						cin >> srcGateNum >> dstGateNum >> dstPortNum;
					}
					while (srcGateNum > num || dstGateNum > num)
					{
						cout << "We don't have the gate!\n Please type again!\n";
						cin >> srcGateNum >> dstGateNum >> dstPortNum;
					}
					while (dstPortNum <0 && dstPortNum > 1)
					{
						cout << "The port only have 0 and 1.\n Please type again!\n";
						cin >> srcGateNum >> dstGateNum >> dstPortNum;
					}
					connect(srcGateNum, dstGateNum, dstPortNum);
				}
				gui.clear();
			}
			if (choice == '3')
			{
				display();
				if (num < 2)
				{
					cout << "Please create two gates first!\n";
					cout << "Please type anything to continue!\n";
					char systemPause;
					cin >> systemPause;
				}
				else
				{
					gui.gateConnectPage();
					int srcGateNum, dstGateNum, dstPortNum;
					cin >> srcGateNum >> dstGateNum >> dstPortNum;
					while (srcGateNum == dstGateNum)
					{
						cout << "The two gates must be separate gates !\n";
						cout << "Please type again!\n";
						cin >> srcGateNum >> dstGateNum >> dstPortNum;
					}
					while (srcGateNum > num || dstGateNum > num)
					{
						cout << "We don't have the gate!\n Please type again!\n";
						cin >> srcGateNum >> dstGateNum >> dstPortNum;
					}
					while (dstPortNum < 0 || dstPortNum > 1)
					{
						cout << "The port only have 0 and 1.\n Please type again!\n";
						cin >> srcGateNum >> dstGateNum >> dstPortNum;
					}
					disconnect(srcGateNum, dstGateNum, dstPortNum);
				}
				gui.clear();
			}
			if (choice == '4')
			{
				runMainProgram();
				gui.clear();
			}
			if (choice == '5')
			{
				gui.clear();
				cout << "\n\n";
				display();
			}
			if (choice == '6')
			{
				gui.clear();
				clear();
			}
			if (choice == '7')
			{
				display();
				bool temp = false;
				for (int i = 0; i < MAXGATE; i++)
				{
					if (store[i] != NULL)
					{
						if (store[i]->name() == "Port")
							temp = true;
					}
				}
				if (!temp)
				{
					cout << "You must create a port first!\n";
					cout << "Please type anything to continue!\n";
					char systemPause;
					cin >> systemPause;
				}
				if (temp)
				{
					gui.setPort();
					int portNum;
					char level;
					cin >> portNum >> level;
					while (portNum > num || level<'0' || level>'1')
					{
						cout << "You type the wrong port number or wrong electrical level.\n Please type again.\n";
						cin >> portNum >> level;
					}
					setPort(portNum, level-'0');
				}
				else
				{
					cout << "Please create a port first!\n";
				}
			}
			gui.firstPage();
			cin >> choice;
		}
	}
};