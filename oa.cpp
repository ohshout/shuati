#include <bits/stdc++.h>

using namespace std;

struct orderInfo {
	string op;
	int price;
	//orderInfo (string o, int p) : op (o), price (p) {};
};

class matchEngine {
	private:
		//orderId --> <price, iterator>
		using LIST_IT = list<pair<string, int>>::iterator;
		map<string, pair<orderInfo, LIST_IT>> orderMap;
		//price --> <orderid, qty>
		map<int, list<pair<string, int>>> buyMap; 
		map<int, list<pair<string, int>>> sellMap; 
		void matchSells (string id, int buyPrice, int& buyQty);
		void matchBuys (string id, int sellPrice, int& sellQty);
		int processLine ();
		//int processLine (ifstream& fin);
		void printBook();
		void saveOrder(string id, int price, int qty, string op);
		void cancelOrder(string id);
		void modifyOrder (string id, string bs_op, int price, int qty);
	public:
		void startEngine();
		
};

void matchEngine::printBook()
{
	cout << "SELL:" << endl;
	for (auto it = sellMap.rbegin(); it != sellMap.rend(); it++) {
		//for each entry, sum qty of orders
		int sum = 0;
		auto &sellList = it->second;
		for (auto lit = sellList.begin(); lit != sellList.end(); lit++)
		{
			sum += lit->second;
		}
		cout << it->first << " " << sum << endl;
	}

	cout << "BUY:" << endl;
	for (auto it = buyMap.rbegin(); it != buyMap.rend(); it++) {
		//for each entry, sum qty of orders
		int sum = 0;
		auto &buyList = it->second;
		for (auto lit = buyList.begin(); lit != buyList.end(); lit++)
		{
			sum += lit->second;
		}
		cout << it->first << " " << sum << endl;
	}
}

void matchEngine::startEngine() {
	//ifstream fin("testt.txt");
	//while (processLine(fin));
	while (processLine());
}

void matchEngine::matchBuys (string sellId, int sellPrice, int& sellQty)
{
	//find the highest buy price
	for (auto it = buyMap.rbegin(); it != buyMap.rend(); it++) {
		int buyPrice = it->first;
		if (buyPrice < sellPrice) {
			//sell price higher than buy
			return;
		} else {
			//this is the highest price among those higher than sell.
			//now find the earliest one
			auto &buyList = it->second;
			auto lit = buyList.begin();
			while (lit != buyList.end()) {
				//trade
				string buyId = lit->first;
				int buyQty = lit->second;
				int tradeQty = min(buyQty, sellQty);
				//print
				cout << "TRADE " << buyId << " " << buyPrice \
					<< " " << tradeQty << " " << \
					sellId << " " << sellPrice << " " << tradeQty << endl;
				//update buyMap
				buyQty -= tradeQty;
				if (buyQty == 0) {
					//erase it from sellList
					buyList.erase(lit++);
					//if (sellList.size() == 0) {
					//	//erase it from sellMap
					//	sellMap.erase(it);
					//}
				} else {
					lit->second -= tradeQty;
				}
				//update buy
				sellQty -= tradeQty;
				if (sellQty == 0)
					return;
			}
		}
	}
}


void matchEngine::matchSells (string buyId, int buyPrice, int& buyQty)
{
	//find the lowest sell price
	for (auto it = sellMap.begin(); it != sellMap.end(); it++) {
		int sellPrice = it->first;
		if (sellPrice > buyPrice) {
			//sell price higher than buy
			return;
		} else {
			//this is the lowest price among those lower than buy.
			//now find the earliest one
			auto &sellList = it->second;
			auto lit = sellList.begin();
			while (lit != sellList.end()) {
				//trade
				string sellId = lit->first;
				int sellQty = lit->second;
				int tradeQty = min(buyQty, sellQty);
				//print
				cout << "TRADE " << sellId << " " << sellPrice \
					<< " " << tradeQty << " " << buyId << " " \
					<< buyPrice << " " << tradeQty << endl;
				//update sellMap
				sellQty -= tradeQty;
				if (sellQty == 0) {
					//erase it from sellList
					sellList.erase(lit++);
					//if (sellList.size() == 0) {
					//	//erase it from sellMap
					//	sellMap.erase(it);
					//}
				} else {
					lit->second -= tradeQty;
				}
				//update buy
				buyQty -= tradeQty;
				if (buyQty == 0)
					return;
			}
		}
	}
}

void matchEngine::saveOrder(string id, int price, int qty, string op)
{
	map<int, list<pair<string, int>>> &gMap = 
		(op == "BUY") ? buyMap : sellMap; 
	gMap[price].push_back({id, qty});
	auto it = gMap[price].end();
	it--; //it points to the last list node
	orderInfo oi {id, price};
	orderMap[id] = {oi, it};
}

void matchEngine::modifyOrder (string id, string bs_op,
		int price, int qty)
{
	if (orderMap.find(id) == orderMap.end())
		return;
	else {
		map<int, list<pair<string, int>>> &gMap = 
			(bs_op == "BUY") ? buyMap : sellMap; 
		int old_price = (orderMap[id].first).price;
		auto bsList = gMap[old_price];
		//remove the old order
		bsList.erase(orderMap[id].second);
		orderMap.erase(id);
		//save the new order
		saveOrder(id, price, qty, bs_op);
	}
}

void matchEngine::cancelOrder (string id)
{
	if (orderMap.find(id) == orderMap.end())
		return;
	else {
		string op = (orderMap[id].first).op;
		map<int, list<pair<string, int>>> &gMap = 
			(op == "BUY") ? buyMap : sellMap; 
		int price = (orderMap[id].first).price;
		gMap[price].erase(orderMap[id].second);
	}
}

//int matchEngine::processLine (ifstream& fin)
int matchEngine::processLine ()
{
	string line;
	//saved in line
	auto& ret = std::getline (std::cin, line);
	//auto& ret = std::getline (fin, line);
	if (!ret) {
		//end of input
		return 0;
	}
	std::istringstream iss (line);
	//get operator of the line
	string op;
	iss >> op;

	//parse operator
	if (op == "BUY" || op == "SELL") {
		//get type
		string type;
		iss >> type;
		//get price
		string _price;
		iss >> _price;
		int price = stoi(_price);
		if (price <= 0) {
			return 1;
		}
		//get qty
		string _qty;
		iss >> _qty;
		int qty = stoi(_qty);
		if (qty <= 0) {
			return 1;
		}
		//get id
		string id;
		iss >> id;
		if (id == "") {
			return 1;
		}

		if (op == "BUY") {
			//find pending sells to match
			matchSells(id, price, qty);
		} else {
			//find pending buys to match
			matchBuys(id, price, qty);
		}

		if (qty > 0) {
			//still qty left
			//check type first
			if (type == "IOC") {
				//do nothing, discard
			} else {
				//save it for possible later sell/buy
				saveOrder (id, price, qty, op);
			}
		}
	} else if (op == "MODIFY") {
		string id;
		iss >> id;
		if (id == "")
			return 1;
		string bs_op;
		iss >> bs_op;
		//get price
		string _price;
		iss >> _price;
		int price = stoi(_price);
		if (price <= 0) {
			return 1;
		}
		//get qty
		string _qty;
		iss >> _qty;
		int qty = stoi(_qty);
		if (qty <= 0) {
			return 1;
		}
		modifyOrder (id, bs_op, price, qty);
	} else if (op == "CANCEL") {
		string id;
		iss >> id;
		if (id == "")
			return 1;
		cancelOrder(id);
	} else if (op == "PRINT") {
		printBook();
	}

	return 1;
}

int main()
{
	matchEngine me;
	me.startEngine();
}


