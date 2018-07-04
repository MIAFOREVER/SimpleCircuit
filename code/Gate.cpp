#pragma once
#include<iostream>
#include<string>
using namespace std;
#define PORTSIZE 20
struct node
{
	int input[2];
	int output;
	int nodeId;
	node* next[PORTSIZE];
	node* prev[2];
};
typedef struct node node;
class Gate
{
public:
	virtual string name() = 0;
	virtual void connect(Gate*, int) = 0;
	virtual void disconnect(Gate*, int) = 0;
	virtual void run() = 0;
	virtual node* getNode() = 0;
	virtual void setPortState(int state) = 0;
	virtual void printError(int errorNum) = 0;
	virtual int getId() = 0;
	virtual void setId(int num) = 0;
	void clear(node* gate)
	{
		delete gate;
	}
};
class Port :public Gate
{
public:
	int errorNum;
	node * now;
	int portState;
	string portName = "Port";
	int getId()
	{
		return now->nodeId;
	}
	void setId(int num)
	{
		now->nodeId = num;
	}
	Port()
	{
		now = new node();
		now->input[0] = -1;
		now->input[1] = -1;
		now->output = -1;
		now->prev[0] = NULL;
		now->prev[1] = NULL;
		for (int i = 0; i < 20; i++)
			now->next[i] = NULL;
	}
	~Port()
	{
		clear(now);
	}
	virtual string name()
	{
		return portName;
	}
	int findFreePort()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->next[i] == NULL)
			{
				return i;
			}
		}
		return -1;
	}
	virtual node* getNode()
	{
		return now;
	}
	virtual void connect(Gate* gate,int dstNum)
	{
		int num = findFreePort();
		if (num != -1)
		{
			now->next[num] = gate->getNode();
			gate->getNode()->prev[dstNum] = now;
		}
		else
		{
			cout << "connect fail!";
		}
	}
	virtual void disconnect(Gate* gate, int dstNum)
	{
		node* temp = gate->getNode()->prev[dstNum];
		node* nowTemp=gate->getNode();
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (temp->next[i] == nowTemp)
			{
				temp->next[i] = NULL;
			}
		}
		gate->getNode()->prev[dstNum] = NULL;
	}
	virtual void setPortState(int state)
	{
		portState = state;
		now->input[0] = state;
	}
	virtual void run()
	{
		now->output = now->input[0];
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->next[i] != NULL)
			{
				if (now->next[i]->prev[0] == now)
					now->next[i]->input[0] = now->output;
				if (now->next[i]->prev[1] == now)
					now->next[i]->input[1] = now->output;
			}
		}
	}
	virtual void printError(int errorNum)
	{
		if (errorNum == 0)
		{
			cout << "All is well.\n";
		}
		if (errorNum == 1)
		{
			cout << "The gate cause short circuit.\n";
		}
	}
};
class AndGate :public Gate
{
public:
	int errorNum;
	node * now;
	string gateName = "AndGate";
	int getId()
	{
		return now->nodeId;
	}
	void setId(int num)
	{
		now->nodeId = num;
	}
	AndGate()
	{
		now = new node();
		now = new node();
		now->input[0] = -1;
		now->input[1] = -1;
		now->output = -1;
		now->prev[0] = NULL;
		now->prev[1] = NULL;
		for (int i = 0; i < 20; i++)
			now->next[i] = NULL;
	}
	~AndGate()
	{
		clear(now);
	}
	virtual string name()
	{
		return gateName;
	}
	virtual void setPortState(int state)
	{
	}
	int findFreePort()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->next[i] == NULL)
			{
				return i;
			}
		}
		return -1;
	}
	virtual node* getNode()
	{
		return now;
	}
	virtual void connect(Gate* gate, int dstNum)
	{
		int num = findFreePort();
		if (num != -1)
		{
			now->next[num] = gate->getNode();
			gate->getNode()->prev[dstNum] = now;
		}
		else
		{
			cout << "Connect fail!";
		}
	}
	virtual void disconnect(Gate* gate, int dstNum)
	{
		node* temp = gate->getNode()->prev[dstNum];
		node* nowTemp = gate->getNode();
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (temp->next[i] == nowTemp)
			{
				temp->next[i] = NULL;
			}
		}
		gate->getNode()->prev[dstNum] = NULL;
	}

	virtual void run()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if ((now->input[0] == 0 && now->input[1] == 0) ||
				(now->input[0] == 1 && now->input[1] == 0) ||
				(now->input[0] == 0 && now->input[1] == 1))
			{
				now->output = 0;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 0;
						}
						if (now->next[i]->input[0] == 1)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 0;
						}
						if (now->next[i]->input[1] == 1)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}
			}
				if (now->input[0] == 1 && now->input[1] == 1)
				{
					now->output = 1;
					if (now->next[i] != NULL)
					{
						if (now->next[i]->prev[0] == now)
						{
							if (now->next[i]->input[0] == -1)
							{
								now->next[i]->input[0] = 1;
							}
							if (now->next[i]->input[0] == 0)
							{
								errorNum = 1;
								now->output = -2;
								break;
							}
						}
						else if (now->next[i]->prev[1] == now)
						{
							if (now->next[i]->input[1] == -1)
							{
								now->next[i]->input[1] = 1;
							}
							if (now->next[i]->input[1] == 0)
							{
								errorNum = 1;
								now->output = -2;
								printError(errorNum);
								break;
							}
						}
					}
				}

			
		}
	}
	virtual void printError(int errorNum)
	{
		if (errorNum == 0)
		{
			cout << "All is well.\n";
		}
		if (errorNum == 1)
		{
			cout << "The gate cause short circuit.\n";
		}
	}
};
class NotGate :public Gate
{
public:
	int errorNum;
	node * now;
	string gateName = "NotGate";
	int getId()
	{
		return now->nodeId;
	}
	void setId(int num)
	{
		now->nodeId = num;
	}
	NotGate()
	{
		now = new node();
		now = new node();
		now->input[0] = -1;
		now->input[1] = -1;
		now->output = -1;
		now->prev[0] = NULL;
		now->prev[1] = NULL;
		for (int i = 0; i < 20; i++)
			now->next[i] = NULL;
	}
	~NotGate()
	{
		clear(now);
	}
	virtual string name()
	{
		return gateName;
	}
	virtual void setPortState(int state)
	{
	}
	int findFreePort()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->next[i] == NULL)
			{
				return i;
			}
		}
		return -1;
	}
	virtual node* getNode()
	{
		return now;
	}
	virtual void connect(Gate* gate, int dstNum)
	{
		int num = findFreePort();
		if (num != -1)
		{
			now->next[num] = gate->getNode();
			gate->getNode()->prev[dstNum] = now;
		}
		else
		{
			cout << "Connect fail!";
		}
	}
	virtual void disconnect(Gate* gate, int dstNum)
	{
		node* temp = gate->getNode()->prev[dstNum];
		node* nowTemp = gate->getNode();
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (temp->next[i] == nowTemp)
			{
				temp->next[i] = NULL;
			}
		}
		gate->getNode()->prev[dstNum] = NULL;
	}

	virtual void run()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->input[0] == 0)
			{
				now->output = 1;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 1;
						}
						if (now->next[i]->input[0] == 0)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 1;
						}
						if (now->next[i]->input[1] == 0)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}
			}
			if (now->input[0] == 1)
			{
				now->output = 0;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 0;
						}
						if (now->next[i]->input[0] == 1)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 0;
						}
						if (now->next[i]->input[1] == 1)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}
			}

		}
	}
	virtual void printError(int errorNum)
	{
		if (errorNum == 0)
		{
			cout << "All is well.\n";
		}
		if (errorNum == 1)
		{
			cout << "The gate cause short circuit.\n";
		}
	}
};
class OrGate :public Gate
{
public:
	int errorNum;
	node * now;
	string gateName = "OrGate";
	int getId()
	{
		return now->nodeId;
	}
	void setId(int num)
	{
		now->nodeId = num;
	}
	OrGate()
	{
		now = new node();
		now = new node();
		now->input[0] = -1;
		now->input[1] = -1;
		now->output = -1;
		now->prev[0] = NULL;
		now->prev[1] = NULL;
		for (int i = 0; i < 20; i++)
			now->next[i] = NULL;
	}
	~OrGate()
	{
		clear(now);
	}
	virtual string name()
	{
		return gateName;
	}
	virtual void setPortState(int state)
	{
	}
	int findFreePort()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->next[i] == NULL)
			{
				return i;
			}
		}
		return -1;
	}
	virtual node* getNode()
	{
		return now;
	}
	virtual void connect(Gate* gate, int dstNum)
	{
		int num = findFreePort();
		if (num != -1)
		{
			now->next[num] = gate->getNode();
			gate->getNode()->prev[dstNum] = now;
		}
		else
		{
			cout << "Connect fail!";
		}
	}
	virtual void disconnect(Gate* gate, int dstNum)
	{
		node* temp = gate->getNode()->prev[dstNum];
		node* nowTemp = gate->getNode();
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (temp->next[i] == nowTemp)
			{
				temp->next[i] = NULL;
			}
		}
		gate->getNode()->prev[dstNum] = NULL;
	}

	virtual void run()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if ((now->input[0] == 1 && now->input[1] == 1) ||
				(now->input[0] == 1 && now->input[1] == 0) ||
				(now->input[0] == 0 && now->input[1] == 1))
			{
				now->output = 1;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 1;
						}
						if (now->next[i]->input[0] == 0)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 1;
						}
						if (now->next[i]->input[1] == 0)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}
			}
			if (now->input[0] == 0 && now->input[1] == 0)
			{
				now->output = 0;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 0;
						}
						if (now->next[i]->input[0] == 1)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 0;
						}
						if (now->next[i]->input[1] == 1)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}

			}
		}
	}
	virtual void printError(int errorNum)
	{
		if (errorNum == 0)
		{
			cout << "All is well.\n";
		}
		if (errorNum == 1)
		{
			cout << "The gate cause short circuit.\n";
		}
	}
};
class XorGate :public Gate
{
public:
	int errorNum;
	node * now;
	string gateName = "XorGate";
	int getId()
	{
		return now->nodeId;
	}
	void setId(int num)
	{
		now->nodeId = num;
	}
	XorGate()
	{
		now = new node();
		now = new node();
		now->input[0] = -1;
		now->input[1] = -1;
		now->output = -1;
		now->prev[0] = NULL;
		now->prev[1] = NULL;
		for (int i = 0; i < 20; i++)
			now->next[i] = NULL;
	}
	~XorGate()
	{
		clear(now);
	}
	virtual string name()
	{
		return gateName;
	}
	virtual void setPortState(int state)
	{
	}
	int findFreePort()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (now->next[i] == NULL)
			{
				return i;
			}
		}
		return -1;
	}
	virtual node* getNode()
	{
		return now;
	}
	virtual void connect(Gate* gate, int dstNum)
	{
		int num = findFreePort();
		if (num != -1)
		{
			now->next[num] = gate->getNode();
			gate->getNode()->prev[dstNum] = now;
		}
		else
		{
			cout << "Connect fail!";
		}
	}
	virtual void disconnect(Gate* gate, int dstNum)
	{
		node* temp = gate->getNode()->prev[dstNum];
		node* nowTemp = gate->getNode();
		for (int i = 0; i < PORTSIZE; i++)
		{
			if (temp->next[i] == nowTemp)
			{
				temp->next[i] = NULL;
			}
		}
		gate->getNode()->prev[dstNum] = NULL;
	}

	virtual void run()
	{
		for (int i = 0; i < PORTSIZE; i++)
		{
			if ((now->input[0] == 1 && now->input[1] == 0) ||
				(now->input[0] == 0 && now->input[1] == 1))
			{
				now->output = 1;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 1;
						}
						if (now->next[i]->input[0] == 0)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 1;
						}
						if (now->next[i]->input[1] == 0)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}
			}
			if ((now->input[0] == 1 && now->input[1] == 1) || 
				(now->input[0] == 0 && now->input[1] == 0))
			{
				now->output = 0;
				if (now->next[i] != NULL)
				{
					if (now->next[i]->prev[0] == now)
					{
						if (now->next[i]->input[0] == -1)
						{
							now->next[i]->input[0] = 0;
						}
						if (now->next[i]->input[0] == 1)
						{
							errorNum = 1;
							now->output = -2;
							break;
						}
					}
					else if (now->next[i]->prev[1] == now)
					{
						if (now->next[i]->input[1] == -1)
						{
							now->next[i]->input[1] = 0;
						}
						if (now->next[i]->input[1] == 1)
						{
							errorNum = 1;
							now->output = -2;
							printError(errorNum);
							break;
						}
					}
				}

			}
		}
	}
	virtual void printError(int errorNum)
	{
		if (errorNum == 0)
		{
			cout << "All is well.\n";
		}
		if (errorNum == 1)
		{
			cout << "The gate cause short circuit.\n";
		}
	}
};