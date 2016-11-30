#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <queue>
#include <functional>

typedef std::pair<double, double> node_type;

/*
辿りつけない場合は空のvectorを返す
*/
std::vector<int> Solve();

double Dist(const node_type& pos, const node_type& to) {
	return std::hypot(to.first - pos.first, to.second - pos.second);
}

int main()
{
	auto result = Solve();
	if (result.empty()) {
		std::cout << "辿りつけません" << std::endl;
		return 0;
	}

	std::cout << "ルートは" << std::endl;
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i];
		if (i != result.size() - 1) {
			std::cout << " -> ";
		}
	}
	std::cout << std::endl;
	getchar(); getchar();
	return 0;
}

std::vector<int> Solve() {
	std::vector<node_type> nodes = {
		std::make_pair(2, 2), //0
		std::make_pair(2, 5), //1
		std::make_pair(2, 6), //2
		std::make_pair(2, 7.5), //3
		std::make_pair(2, 8), //4
		std::make_pair(2, 10), //5
		std::make_pair(4, 2), //6
		std::make_pair(6, 2), //7
		std::make_pair(6, 3), //8
		std::make_pair(6, 4), //9
		std::make_pair(6.5, 7), //10
		std::make_pair(6.5, 8), //11
		std::make_pair(6.5, 10), //12
		std::make_pair(8, 3), //13
		std::make_pair(8, 4), //14
		std::make_pair(8, 7), //15
		std::make_pair(8, 10), //16
	};
	//                   ノードの番号
	std::vector<std::pair<int, int>> edges = {
		std::make_pair(0, 1),
		std::make_pair(1, 2),
		std::make_pair(2, 3),
		std::make_pair(3, 4),
		std::make_pair(4, 5),
		std::make_pair(4, 11),
		std::make_pair(5, 12),
		std::make_pair(0, 6),
		std::make_pair(6, 7),
		std::make_pair(7, 8),
		std::make_pair(8, 9),
		std::make_pair(9, 10),
		std::make_pair(10, 11),
		std::make_pair(11, 12),
		std::make_pair(8, 13),
		std::make_pair(13, 14),
		std::make_pair(14, 15),
		std::make_pair(10, 15),
		std::make_pair(15, 16),
		std::make_pair(12, 16),
		std::make_pair(1, 0),
		std::make_pair(2, 1),
		std::make_pair(3, 2),
		std::make_pair(4, 3),
		std::make_pair(11, 4),
		std::make_pair(5, 4),
		std::make_pair(12, 5),
		std::make_pair(6, 0),
		std::make_pair(7, 6),
		std::make_pair(8, 7),
		std::make_pair(9, 8),
		std::make_pair(10, 9),
		std::make_pair(11, 10),
		std::make_pair(12, 11),
		std::make_pair(13, 8),
		std::make_pair(14, 13),
		std::make_pair(15, 14),
		std::make_pair(15, 10),
		std::make_pair(16, 15),
		std::make_pair(16, 12),
	};

	std::vector<double> weight = {
		Dist(nodes[0], nodes[1]),
		Dist(nodes[1], nodes[2]),
		Dist(nodes[2], nodes[3]),
		Dist(nodes[3], nodes[4]),
		Dist(nodes[4], nodes[5]),
		Dist(nodes[4], nodes[11]),
		Dist(nodes[5], nodes[12]),
		Dist(nodes[0], nodes[6]),
		Dist(nodes[6], nodes[7]),
		Dist(nodes[7], nodes[8]),
		Dist(nodes[8], nodes[9]),
		Dist(nodes[9], nodes[10]),
		Dist(nodes[10], nodes[11]),
		Dist(nodes[11], nodes[12]),
		Dist(nodes[8], nodes[13]),
		Dist(nodes[13], nodes[14]),
		Dist(nodes[14], nodes[15]),
		Dist(nodes[10], nodes[15]),
		Dist(nodes[15], nodes[16]),
		Dist(nodes[12], nodes[16]),
		Dist(nodes[0], nodes[1]),
		Dist(nodes[1], nodes[2]),
		Dist(nodes[2], nodes[3]),
		Dist(nodes[3], nodes[4]),
		Dist(nodes[4], nodes[5]),
		Dist(nodes[4], nodes[11]),
		Dist(nodes[5], nodes[12]),
		Dist(nodes[0], nodes[6]),
		Dist(nodes[6], nodes[7]),
		Dist(nodes[7], nodes[8]),
		Dist(nodes[8], nodes[9]),
		Dist(nodes[9], nodes[10]),
		Dist(nodes[10], nodes[11]),
		Dist(nodes[11], nodes[12]),
		Dist(nodes[8], nodes[13]),
		Dist(nodes[13], nodes[14]),
		Dist(nodes[14], nodes[15]),
		Dist(nodes[10], nodes[15]),
		Dist(nodes[15], nodes[16]),
		Dist(nodes[12], nodes[16]),
	};

	int pos = 16;
	int goal = 9;
	std::set<int> visited;
	std::priority_queue<std::pair<double, std::vector<int>>, std::vector<std::pair<double, std::vector<int>>>, std::greater<std::pair<double, std::vector<int>>>> q; //次の地点に進んだ際のコスト, 次の地点を含めた経路
	q.push(std::make_pair(0, std::vector<int>() = {pos}));

	while (!q.empty()) {
		//キューの中で最も評価値の高いものを取り出す
		auto node = q.top(); q.pop();
		auto edge = std::make_pair(node.second.back(), 0);

		//その場所を訪れる
		visited.insert(node.second.back());

		//それがゴールなら終了
		if (node.second.back() == goal) {
			return node.second;
		}

		for (int i = 0; i < nodes.size(); i++) {
			edge.second = i;
			//移動できる場合
			auto next = std::find(edges.begin(), edges.end(), edge);
			if (next != edges.end()) {
				//進む予定の場所に未到達ならキューに加える
				if (visited.find(i) == visited.end()) {
					//コストを計算
					double cost = node.first + Dist(nodes[edge.first], nodes[edge.second]);
					//移動先を追加
					auto nextNode = node.second;
					nextNode.push_back(edge.second);
					//キューに追加
					q.push(std::make_pair(cost, nextNode));
				}
			}
		}
	}
	//辿りつけない
	return std::vector<int>();
}