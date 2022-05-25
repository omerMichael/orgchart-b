#include "OrgChart.hpp"
#include <algorithm>

namespace ariel
{
	void delete_all_nodes_in_tree(Tree* root) {
		if (root != nullptr) {
			for (auto* child: root->children) {
				delete_all_nodes_in_tree(child);
			}
			delete root;
		}
	}

	Tree* copy_tree(Tree* src_root) {
		Tree* new_root = nullptr;
		if (src_root != nullptr) {
			new_root = new Tree;

			new_root->value = src_root->value;

			for (auto *child: src_root->children) {
				new_root->children.push_back(copy_tree(child));
			}
		}
		return new_root;
	}

	void map_tree_nodes(Tree* root, std::vector<std::pair<size_t, Tree*>>& node_depth_table, size_t curr_depth) {
		if (root != nullptr) {
			node_depth_table.push_back(std::pair<size_t, Tree*>(curr_depth++, root));

			for (auto* child: root->children) {
				map_tree_nodes(child, node_depth_table, curr_depth);
			}
		}
	}

	bool compare_heights(std::pair<size_t, Tree*> elem1, std::pair<size_t, Tree*> elem2) {
		// Prefer to go to the last one added
		if (elem1.first == elem2.first) {
			return true;
		}
		return elem1.first < elem2.first;
	}

	void queue_tree_nodes_preorder(Tree* root, std::queue<Tree*>& queue) {
		if (root != nullptr) {
			queue.push(root);
			
			for (auto* child: root->children) {
				queue_tree_nodes_preorder(child, queue);
			}
		}
	}

	OrgChart::LevelOrderIterator::LevelOrderIterator(Tree* node): m_node(node) {}

	OrgChart::LevelOrderIterator::LevelOrderIterator(const LevelOrderIterator& other):
		m_node(other.m_node), m_iteration_queue(other.m_iteration_queue) {}

	OrgChart::LevelOrderIterator& OrgChart::LevelOrderIterator::operator=(const LevelOrderIterator& other) {
		if (this == &other) {
			return *this;
		}

		m_node = other.m_node;
		return *this;
	}

	OrgChart::LevelOrderIterator::LevelOrderIterator(LevelOrderIterator&& other) noexcept: m_node(other.m_node) {
		other.m_node = nullptr;
		m_iteration_queue = std::move(other.m_iteration_queue);
	}

	OrgChart::LevelOrderIterator& OrgChart::LevelOrderIterator::operator=(LevelOrderIterator&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		m_node = other.m_node;
		other.m_node = nullptr;

		return *this;
	}

	OrgChart::LevelOrderIterator& OrgChart::LevelOrderIterator::operator++() {
		for (auto* child: m_node->children) {
			// Push all of my children's children into the queue
			m_iteration_queue.push(child);
		}

		if (m_iteration_queue.empty()) {
			m_node = nullptr;
			return *this;
		}

		m_node = m_iteration_queue.front();
		m_iteration_queue.pop();
		return *this;
	}

	bool OrgChart::LevelOrderIterator::operator==(const OrgChart::LevelOrderIterator& other) const {
		if (m_node == nullptr) {
			return other.m_node == nullptr;
		}
		return other.m_node != nullptr && m_node->value == other.m_node->value;
	}

	bool OrgChart::LevelOrderIterator::operator!=(const OrgChart::LevelOrderIterator& other) const {
		return !(*this == other);
	}

	std::string& OrgChart::LevelOrderIterator::operator*() {
		return m_node->value;
	}

	std::string* OrgChart::LevelOrderIterator::operator->() {
		return &m_node->value;
	}

	OrgChart::ReverseOrderIterator& OrgChart::ReverseOrderIterator::operator++() {
		if (m_iteration_vector.empty()) {
			m_node = nullptr;
			return *this;
		}

		m_node = m_iteration_vector.back().second;
		m_iteration_vector.pop_back();
		return *this;
	}

	bool OrgChart::ReverseOrderIterator::operator==(const OrgChart::ReverseOrderIterator& other) const {
		if (m_node == nullptr) {
			return other.m_node == nullptr;
		}
		return other.m_node != nullptr && m_node->value == other.m_node->value;
	}

	bool OrgChart::ReverseOrderIterator::operator!=(const OrgChart::ReverseOrderIterator& other) const {
		return !(*this == other);
	}

	std::string& OrgChart::ReverseOrderIterator::operator*() {
		return m_node->value;
	}

	std::string* OrgChart::ReverseOrderIterator::operator->() {
		return &m_node->value;
	}

	OrgChart::PreorderIterator& OrgChart::PreorderIterator::operator++() {
		if (m_iteration_queue.empty()) {
			m_node = nullptr;
			return *this;
		}

		m_node = m_iteration_queue.front();
		m_iteration_queue.pop();
		return *this;
	}

	bool OrgChart::PreorderIterator::operator==(const OrgChart::PreorderIterator& other) const {
		if (m_node == nullptr) {
			return other.m_node == nullptr;
		}
		return other.m_node != nullptr && m_node->value == other.m_node->value;
	}

	bool OrgChart::PreorderIterator::operator!=(const OrgChart::PreorderIterator& other) const {
		return !(*this == other);
	}

	std::string& OrgChart::PreorderIterator::operator*() {
		return m_node->value;
	}

	std::string* OrgChart::PreorderIterator::operator->() {
		return &m_node->value;
	}

	OrgChart::ReverseOrderIterator::ReverseOrderIterator(Tree* node): m_node(node) {
		if (node != nullptr) {
			map_tree_nodes(node, m_iteration_vector, 0);

			std::sort(m_iteration_vector.begin(), m_iteration_vector.end(), compare_heights);
			
			m_node = m_iteration_vector.back().second;
			m_iteration_vector.pop_back();
		}
	}

	OrgChart::ReverseOrderIterator::ReverseOrderIterator(const ReverseOrderIterator& other): m_node(other.m_node) {}

	OrgChart::ReverseOrderIterator& OrgChart::ReverseOrderIterator::operator=(const ReverseOrderIterator& other) {
		if (this == &other) {
			return *this;
		}
		m_node = other.m_node;
		return *this;
	}

	OrgChart::ReverseOrderIterator::ReverseOrderIterator(ReverseOrderIterator&& other) noexcept: m_node(other.m_node) {
		other.m_node = nullptr;
	}

	OrgChart::ReverseOrderIterator& OrgChart::ReverseOrderIterator::operator=(ReverseOrderIterator&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		m_node = other.m_node;
		other.m_node = nullptr;
		return *this;
	}


	OrgChart::PreorderIterator::PreorderIterator(Tree* node): m_node(node) {
		if (node != nullptr) {
			queue_tree_nodes_preorder(node, m_iteration_queue);

			// The root has already been set as the current node
			m_iteration_queue.pop();
		}
	}

	OrgChart::PreorderIterator::PreorderIterator(const PreorderIterator& other): m_node(other.m_node) {}

	OrgChart::PreorderIterator& OrgChart::PreorderIterator::operator=(const PreorderIterator& other) {
		if (this == &other) {
			return *this;
		}

		m_node = other.m_node;
		return *this;
	}

	OrgChart::PreorderIterator::PreorderIterator(PreorderIterator&& other) noexcept: m_node(other.m_node) {
		other.m_node = nullptr;
	}

	OrgChart::PreorderIterator& OrgChart::PreorderIterator::operator=(PreorderIterator&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		m_node = other.m_node;
		other.m_node = nullptr;
		return *this;
	}

	OrgChart::~OrgChart() {
		delete_all_nodes_in_tree(m_root);
	}

	OrgChart::OrgChart(): m_root(nullptr) {}

	OrgChart::OrgChart(const OrgChart& other): m_root(copy_tree(other.m_root)) {}

	OrgChart& OrgChart::operator=(const OrgChart& other) {
		if (this == &other) {
			return *this;
		}

		m_root = copy_tree(other.m_root);
		return *this;
	}

	OrgChart::OrgChart(OrgChart&& other) noexcept: m_root(other.m_root) {
		other.m_root = nullptr;
	}

	OrgChart& OrgChart::operator=(OrgChart&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		m_root = other.m_root;
		other.m_root = nullptr;
		return *this;
	}

	OrgChart& OrgChart::add_root(const std::string& new_root) {
		if (m_root != nullptr) {
			m_root->value = new_root;
			return *this;
		}

		m_root = new Tree;
		m_root->value = new_root;
		return *this;
	}

	Tree* find_node_by_value(Tree* root_node, const std::string& value) {
		if (root_node == nullptr) {
			return nullptr;
		}
		
		// If this is the correct node, return it!
		if (root_node->value == value) {
			return root_node;
		}

		Tree* child_res = nullptr;
		// Go over the children of the current node
		for (Tree* child: root_node->children) {
			child_res = find_node_by_value(child, value);

			// If the required node was found under your child, return it
			if (child_res != nullptr) {
				return child_res;
			}
		}

		return nullptr;
	}

	OrgChart& OrgChart::add_sub(const std::string& parent, const std::string& child) {
		if (m_root == nullptr) {
			// Throw an exception
			throw std::logic_error("Tried to add subordinate to chart when there is no root");
		}

		Tree* new_child_parent = find_node_by_value(m_root, parent);

		if (new_child_parent == nullptr) {
			// Throw an exception
			throw std::logic_error("Tried to add subordinate to a non-existent parent");
		}

		Tree* new_child = new Tree;
		new_child->value = child;

		new_child_parent->children.push_back(new_child);
		return *this;
	}

	std::ostream& operator<<(std::ostream& output, const OrgChart& me) {
		return output;
	}

	OrgChart::LevelOrderIterator OrgChart::begin() {
		return begin_level_order();
	}

	OrgChart::LevelOrderIterator OrgChart::end() {
		return end_level_order();
	}
	
	OrgChart::LevelOrderIterator OrgChart::begin_level_order() {
		if (m_root == nullptr) {
			throw std::logic_error("Can't get iterator of empty chart");
		}
		return OrgChart::LevelOrderIterator(m_root);
	}

	OrgChart::LevelOrderIterator OrgChart::end_level_order() {
		if (m_root == nullptr) {
			throw std::logic_error("Can't get iterator of empty chart");
		}
		return OrgChart::LevelOrderIterator(nullptr);
	}

	OrgChart::ReverseOrderIterator OrgChart::begin_reverse_order() {
		if (m_root == nullptr) {
			throw std::logic_error("Can't get iterator of empty chart");
		}
		return OrgChart::ReverseOrderIterator(m_root);
	}

	OrgChart::ReverseOrderIterator OrgChart::reverse_order() {
		if (m_root == nullptr) {
			throw std::logic_error("Can't get iterator of empty chart");
		}
		return OrgChart::ReverseOrderIterator(nullptr);
	}

	OrgChart::PreorderIterator OrgChart::begin_preorder() {
		if (m_root == nullptr) {
			throw std::logic_error("Can't get iterator of empty chart");
		}
		return OrgChart::PreorderIterator(m_root);
	}

	OrgChart::PreorderIterator OrgChart::end_preorder() {
		if (m_root == nullptr) {
			throw std::logic_error("Can't get iterator of empty chart");
		}
		return OrgChart::PreorderIterator(nullptr);
	}
}
