#include <iterator>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

namespace ariel {
	struct Tree {
		std::string value;
		std::vector<Tree*> children;
	};

	/**
	 * @brief Helper function to recursively find a node in the tree by value
	 *
	 * @param root_node - The tree to search in
	 *
	 * @param value - The value to search
	 *
	 * @return A pointer to the required node, nullptr if doesn't exist
	 * */
	Tree* find_node_by_value(Tree* root_node, const std::string& value);

	/**
	 * @brief Helper function to free all memory allocated in the tree
	 * */
	void delete_all_nodes_in_tree(Tree* root); 

	/**
	 * @brief Helper function to recursively copy all the nodes in the tree
	 * */
	Tree* copy_tree(Tree* src_root);

	/**
	 * @brief helper function to map tree nodes to their height
	 * */
	void map_tree_nodes(Tree* root, std::vector<std::pair<size_t, Tree*>>& node_depth_table, size_t curr_depth);

	/**
	 * @brief helper function to compare node heights
	 * */
	bool compare_heights(std::pair<size_t, Tree*> elem1, std::pair<size_t, Tree*> elem2);

	/**
	 * @brief helper function to queue up tree nodes in a preorder traversal algorithm
	 * */
	void queue_tree_nodes_preorder(Tree* root, std::queue<Tree*>& queue);

	class OrgChart {
		public:
			class LevelOrderIterator;

			class ReverseOrderIterator;

			class PreorderIterator;

			OrgChart();

			~OrgChart();

			OrgChart(const OrgChart& other);

			OrgChart& operator=(const OrgChart& other);

			OrgChart(OrgChart&& other) noexcept;

			OrgChart& operator=(OrgChart&& other) noexcept;

			/**
			 * @brief Add a root level rank, will be the head of the 
			 * 		  Chart
			 *	
			 * @param root - The level that will be the head of the 
			 * 				 Chart.
			 * */
			OrgChart& add_root(const std::string& root);

			/**
			 * @brief Add a new child level under a given parent level
			 *
			 * @param parent - the Parent level under which the child will be placed.
			 * 				   NOTE: Must exist already in the Chart
			 *
			 * @param child - the new child level
			 * */
			OrgChart& add_sub(const std::string& parent, const std::string& child);

			/**
			 * @brief Operator overload for stream output
			 *
			 * @param output - The stream to write to
			 *
			 * @param me - The orgchart to write to the stream
			 *
			 * @return The output stream after writing the chart to it
			 * */
			friend std::ostream& operator<<(std::ostream& output, const OrgChart& me);

			/**
			 * @brief Get an iterator over the OrgChart (by default - level order iteration)
			 * */
			LevelOrderIterator begin();

			/**
			 * @brief Get an iterator object to the end of the chart
			 * */
			LevelOrderIterator end();

			/**
			 * @brief Get an iterator over the OrgChart, to be iterated by level order
			 * */
			LevelOrderIterator begin_level_order();

			/**
			 * @brief Get an iterator over to the end of the OrgChart
			 * */
			LevelOrderIterator end_level_order();

			/**
			 * @brief Get an iterator over the OrgChart, to be iterated by reverse order
			 * */
			ReverseOrderIterator begin_reverse_order();

			/**
			 * @brief Get an iterator over to the end of the OrgChart.
			 * */
			ReverseOrderIterator reverse_order();

			/**
			 * @brief Get an iterator over the OrgChart, to be iterated by pre order
			 * */
			PreorderIterator begin_preorder();

			/**
			 * @brief Get an iterator over to the end of the OrgChart.
			 * */
			PreorderIterator end_preorder();

			class LevelOrderIterator: public std::iterator<std::input_iterator_tag, Tree*> {
				public:
					/**
					 * @brief Constructor for the iterator over the OrgChart
					 *
					 * @param node - A pointer to the Tree which holds the data to the orgchart.
					 * */
					explicit LevelOrderIterator(Tree* node);

					~LevelOrderIterator() = default;

					LevelOrderIterator(const LevelOrderIterator& other);

					LevelOrderIterator& operator=(const LevelOrderIterator& other);

					LevelOrderIterator(LevelOrderIterator&& other) noexcept;

					LevelOrderIterator& operator=(LevelOrderIterator&& other) noexcept;

					/**
					 * @brief An operator overload for the increment operator for the iterator over the OrgChart
					 * 		  Will go by level order (go to the next rank by order)
					 *
					 * @return the iterator object to the next rank
					 * */
					LevelOrderIterator& operator++();

					/**
					 * @brief and operator overload for the equals operator, will determine whether
					 * 		  Two iterators are the same
					 * */
					bool operator==(const LevelOrderIterator& other) const;

					/**
					 * @brief and operator overload for the equals operator, will determine whether
					 * 		  Two iterators are not the same
					 * */
					bool operator!=(const LevelOrderIterator& other) const;

					/**
					 * @brief A dereference operator overload for an iterator, will return the held value
					 * */
					std::string& operator*();

					/**
					 * @brief A struct deref oeprator overload for the iterator, will allow access to the held value.
					 * */
					std::string* operator->();

				private:
					Tree* m_node;
					std::queue<Tree*> m_iteration_queue;
			};

			class ReverseOrderIterator: public std::iterator<std::input_iterator_tag, Tree*> {
				public:
					/**
					 * @brief Constructor for the iterator over the OrgChart
					 *
					 * @param node - A pointer to the Tree which holds the data to the orgchart.
					 * */
					explicit ReverseOrderIterator(Tree* node);

					~ReverseOrderIterator() = default;

					ReverseOrderIterator(const ReverseOrderIterator& other);

					ReverseOrderIterator& operator=(const ReverseOrderIterator& other);

					ReverseOrderIterator(ReverseOrderIterator&& other) noexcept;

					ReverseOrderIterator& operator=(ReverseOrderIterator&& other) noexcept;

					/**
					 * @brief An operator overload for the increment operator for the iterator over the OrgChart
					 * 		  Will go by reverse level order (go to the next lower rank by order)
					 *
					 * @return the iterator object to the next rank
					 * */
					ReverseOrderIterator& operator++();

					/**
					 * @brief and operator overload for the equals operator, will determine whether
					 * 		  Two iterators are the same
					 * */
					bool operator==(const ReverseOrderIterator& other) const;
					
					/**
					 * @brief and operator overload for the equals operator, will determine whether
					 * 		  Two iterators are not the same
					 * */
					bool operator!=(const ReverseOrderIterator& other) const;

					/**
					 * @brief A dereference operator overload for an iterator, will return the held value
					 * */
					std::string& operator*();

					/**
					 * @brief A struct deref oeprator overload for the iterator, will allow access to the held value.
					 * */
					std::string* operator->();

				private:
					Tree* m_node;
					std::vector<std::pair<size_t, Tree*>> m_iteration_vector;
			};

			class PreorderIterator: public std::iterator<std::input_iterator_tag, Tree*> {
				public:
					/**
					 * @brief Constructor for the iterator over the OrgChart
					 *
					explicit PreorderIterator(Tree* node);
					 * */
					explicit PreorderIterator(Tree* node);

					~PreorderIterator() = default;

					PreorderIterator(const PreorderIterator& other);

					PreorderIterator& operator=(const PreorderIterator& other);

					PreorderIterator(PreorderIterator&& other) noexcept;

					PreorderIterator& operator=(PreorderIterator&& other) noexcept;

					/**
					 * @brief An operator overload for the increment operator for the iterator over the OrgChart
					 * 		  Will go by preorder over the tree
					 *
					 * @return the iterator object to the next rank
					 * */
					PreorderIterator& operator++();

					/**
					 * @brief and operator overload for the equals operator, will determine whether
					 * 		  Two iterators are the same
					 * */
					bool operator==(const PreorderIterator& other) const;

					/**
					 * @brief and operator overload for the equals operator, will determine whether
					 * 		  Two iterators are not the same
					 * */
					bool operator!=(const PreorderIterator& other) const;


					/**
					 * @brief A dereference operator overload for an iterator, will return the held value
					 * */
					std::string& operator*();

					/**
					 * @brief A struct deref oeprator overload for the iterator, will allow access to the held value.
					 * */
					std::string* operator->();

				private:
					Tree* m_node;
					std::queue<Tree*> m_iteration_queue;
			};

		private:
			Tree* m_root;
	};
}
