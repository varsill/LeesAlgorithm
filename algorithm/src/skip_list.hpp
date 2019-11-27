#pragma once
#include <random>
#include <memory>
#include <vector>
#include <functional>
#include <exception>
#define MAX_H 20

namespace data_structures {
	
	
	//AH ten double-dispatch, jak masz pomysł jak to obejść to pisz
	
	class floating
	{
	protected:
		float val;
	public:
		floating(float a) : val(a) {}
		floating() {}
		static floating min_value;
		static floating max_value;
		
		bool operator< (const floating& a)
		{
			return this->val < a.val;
		}
		
		bool operator== (const floating& a)
		{
			return abs(this->val - a.val) < 0.00000001;
		
		}
		
	};

	
	


	

	floating floating::max_value=floating(1000000000);
	floating floating::min_value = floating(-100000000);

/*
███████╗██╗  ██╗██╗██████╗ ██╗     ██╗███████╗████████╗
██╔════╝██║ ██╔╝██║██╔══██╗██║     ██║██╔════╝╚══██╔══╝
███████╗█████╔╝ ██║██████╔╝██║     ██║███████╗   ██║
╚════██║██╔═██╗ ██║██╔═══╝ ██║     ██║╚════██║   ██║
███████║██║  ██╗██║██║     ███████╗██║███████║   ██║
╚══════╝╚═╝  ╚═╝╚═╝╚═╝     ╚══════╝╚═╝╚══════╝   ╚═╝

██████╗ ███████╗ ██████╗██╗      █████╗ ██████╗  █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
██╔══██╗██╔════╝██╔════╝██║     ██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
██║  ██║█████╗  ██║     ██║     ███████║██████╔╝███████║   ██║   ██║██║   ██║██╔██╗ ██║
██║  ██║██╔══╝  ██║     ██║     ██╔══██║██╔══██╗██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
██████╔╝███████╗╚██████╗███████╗██║  ██║██║  ██║██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
╚═════╝ ╚══════╝ ╚═════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
                                                                            */

        template<class T, class K, int MAX_HEIGHT = MAX_H>
        class skip_list
        {
                public:
                        class node
                        {
                        friend skip_list<T, K, MAX_HEIGHT>;

                        private:
                                T value;
					    protected:
								skip_list<T, K, MAX_HEIGHT>& outer;
								size_t height;
								std::vector<std::shared_ptr<node>> neighbours;
                         public:
								node(skip_list<T, K, MAX_HEIGHT>& outer);
                                node(skip_list<T, K, MAX_HEIGHT>& outer, const T& value);
                                node(skip_list<T, K, MAX_HEIGHT>&outer, size_t height,const T& value);
                                virtual ~node();
                                virtual K get_key();
						};

					
						class guard_node:public node
						{
						private:
							K key;
						public:
							guard_node(skip_list<T, K, MAX_HEIGHT>& outer, const K& key);
							guard_node(skip_list<T, K, MAX_HEIGHT>&outer, K&& key);
							virtual K get_key() override;
							~guard_node();

						};


                typedef std::shared_ptr<node> ptr;

                private:
						size_t size;
                        std::shared_ptr<node> beginning;
                        std::function<K(T)> get_key_function;
                        static size_t get_random_height();
                        std::shared_ptr<node> get_preceeding(const K& key);
                        std::shared_ptr<node> get_preceeding(K&& key);
                public:
                        skip_list(std::function<K(const T&)> get_key_function);
                        ~skip_list();
                        void insert(const T& element);
                        void insert(T&& element);
                        std::pair<bool, T> get_element(const K& key);
                        std::pair<bool, T> get_element(K&& key);

                        T& find_no_smaller_than(const K& key);
                        T& find_no_greater_than(const K& key);
                        void remove(const K& key);
                        void remove(K&& key);
                        void print(size_t from_max_level = MAX_HEIGHT);
						size_t get_size();

        };


/*
███╗   ██╗ ██████╗ ██████╗ ███████╗     ██████╗██╗      █████╗ ███████╗███████╗
████╗  ██║██╔═══██╗██╔══██╗██╔════╝    ██╔════╝██║     ██╔══██╗██╔════╝██╔════╝
██╔██╗ ██║██║   ██║██║  ██║█████╗      ██║     ██║     ███████║███████╗███████╗
██║╚██╗██║██║   ██║██║  ██║██╔══╝      ██║     ██║     ██╔══██║╚════██║╚════██║
██║ ╚████║╚██████╔╝██████╔╝███████╗    ╚██████╗███████╗██║  ██║███████║███████║
╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚══════╝     ╚═════╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝

██╗███╗   ███╗██████╗ ██╗     ███████╗███╗   ███╗███████╗███╗   ██╗████████╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
██║████╗ ████║██╔══██╗██║     ██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
██║██╔████╔██║██████╔╝██║     █████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║   ███████║   ██║   ██║██║   ██║██╔██╗ ██║
██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
██║██║ ╚═╝ ██║██║     ███████╗███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
 */

        template<class T, class K, int MAX_HEIGHT>
        inline skip_list<T, K, MAX_HEIGHT>::node::node(skip_list<T, K, MAX_HEIGHT>& outer, const T & value):value(value), height(get_random_height()), outer(outer)
        {
                neighbours = std::vector<ptr>(height + 1, nullptr);
        }

        template<class T, class K, int MAX_HEIGHT>
        inline skip_list<T, K, MAX_HEIGHT>::node::node(skip_list<T, K, MAX_HEIGHT>& outer, size_t height, const T & value) : value(value), height(height), outer(outer)
        {
                neighbours = std::vector<ptr>(height + 1, nullptr);
        }


		template<class T, class K, int MAX_HEIGHT>
		inline data_structures::skip_list<T, K, MAX_HEIGHT>::node::node(skip_list<T, K, MAX_HEIGHT>& outer):outer(outer), height(MAX_HEIGHT)
		{
			neighbours = std::vector<ptr>(height + 1, nullptr);
		}

		template<class T, class K, int MAX_HEIGHT>
        inline skip_list<T, K, MAX_HEIGHT>::node::~node()
        {
                this->neighbours.clear();
        }

        template<class T, class K, int MAX_HEIGHT>
        inline K skip_list<T, K, MAX_HEIGHT>::node::get_key()
        {
                return outer.get_key_function(this->value);
        }

// ██████╗ ██╗   ██╗ █████╗ ██████╗ ██████╗     ███╗   ██╗ ██████╗ ██████╗ ███████╗                                  
//██╔════╝ ██║   ██║██╔══██╗██╔══██╗██╔══██╗    ████╗  ██║██╔═══██╗██╔══██╗██╔════╝                                  
//██║  ███╗██║   ██║███████║██████╔╝██║  ██║    ██╔██╗ ██║██║   ██║██║  ██║█████╗                                    
//██║   ██║██║   ██║██╔══██║██╔══██╗██║  ██║    ██║╚██╗██║██║   ██║██║  ██║██╔══╝                                    
//╚██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝    ██║ ╚████║╚██████╔╝██████╔╝███████╗                                  
// ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝     ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚══════╝                                  
//                                                                                                                   
//██╗███╗   ███╗██████╗ ██╗     ███████╗███╗   ███╗███████╗███╗   ██╗████████╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
//██║████╗ ████║██╔══██╗██║     ██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
//██║██╔████╔██║██████╔╝██║     █████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║   ███████║   ██║   ██║██║   ██║██╔██╗ ██║
//██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
//██║██║ ╚═╝ ██║██║     ███████╗███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
//╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
                                                                                                                   


		template<class T, class K, int MAX_HEIGHT>
		inline skip_list<T, K, MAX_HEIGHT>::guard_node::guard_node(skip_list<T, K, MAX_HEIGHT>& outer, const K& key):node(outer), key(key)
		{
		}

		template<class T, class K, int MAX_HEIGHT>
		inline skip_list<T, K, MAX_HEIGHT>::guard_node::guard_node(skip_list<T, K, MAX_HEIGHT>& outer, K&& key) :node(outer), key(key)
		{

		}


		template<class T, class K, int MAX_HEIGHT>
		inline skip_list<T, K, MAX_HEIGHT>::guard_node::~guard_node()
		{
			
		}


		template<class T, class K, int MAX_HEIGHT>
		inline K skip_list<T, K, MAX_HEIGHT>::guard_node::get_key()
		{
			return this->key;
		}


/*
███████╗██╗  ██╗██╗██████╗ ██╗     ██╗███████╗████████╗
██╔════╝██║ ██╔╝██║██╔══██╗██║     ██║██╔════╝╚══██╔══╝
███████╗█████╔╝ ██║██████╔╝██║     ██║███████╗   ██║
╚════██║██╔═██╗ ██║██╔═══╝ ██║     ██║╚════██║   ██║
███████║██║  ██╗██║██║     ███████╗██║███████║   ██║
╚══════╝╚═╝  ╚═╝╚═╝╚═╝     ╚══════╝╚═╝╚══════╝   ╚═╝

██╗███╗   ███╗██████╗ ██╗     ███████╗███╗   ███╗███████╗███╗   ██╗████████╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗
██║████╗ ████║██╔══██╗██║     ██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║
██║██╔████╔██║██████╔╝██║     █████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║   ███████║   ██║   ██║██║   ██║██╔██╗ ██║
██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║   ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║
██║██║ ╚═╝ ██║██║     ███████╗███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║   ██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║
╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
 */


        template<class T, class K, int MAX_HEIGHT>
        inline size_t skip_list<T, K, MAX_HEIGHT>::get_random_height()
        {
                        size_t height = 0;
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> dis(0, 1);
                        while ( (dis(gen) == 1) && (height < MAX_HEIGHT)) height++;

                        return height;
        }

        template<class T, class K, int max_height>
        inline std::shared_ptr<typename skip_list<T, K, max_height>::node> skip_list<T, K, max_height>::get_preceeding(K&& key)
        {
                std::unique_ptr<typename skip_list<T, K, max_height>::node> prev = this->beginning;
                int level = prev->height;
                ptr current;
                while (level >= 0)
                {
                        current = prev->neighbours[level];

                        while (get_key_function(current->value) < key)
                        {
                                prev = current;
                                current = current->neighbours[level];
                        }
                        level--;

                }
                return current;
        }

        template<class T, class K, int max_height>
        inline std::shared_ptr<typename skip_list<T, K, max_height>::node > skip_list<T, K, max_height>::get_preceeding(const K & key)
        {
                ptr prev = this->beginning;
                int level = prev->height;
                ptr current;
                while (level >= 0)
                {
                        current = prev->neighbours[level];

                        while (get_key_function(current->value) < key)
                        {
                                prev = current;
                                current = current->neighbours[level];
                        }
                        level--;

                }
                return current;
        }



        template<class T, class K, int MAX_HEIGHT>
        inline skip_list<T, K, MAX_HEIGHT>::skip_list(std::function<K(const T&)> get_key_function) :get_key_function(get_key_function)
        {
				ptr min_guard = std::shared_ptr<guard_node>(new guard_node(*this, K::min_value));
                ptr max_guard = std::shared_ptr<guard_node>(new guard_node(*this, K::max_value));
                this->beginning = min_guard;
                for (size_t i = 0; i <= MAX_HEIGHT; i++)
                {
                        min_guard->neighbours[i] = max_guard;
                }
				size = 0;
        }


        template<class T, class K, int MAX_HEIGHT>
        inline data_structures::skip_list<T, K, MAX_HEIGHT>::~skip_list()
        {
                ptr current = this->beginning;
                while (current != nullptr)
                {
                        ptr next = current->neighbours[0];
                        current.reset();
                        current = next;
                }
        }


        template<class T, class K, int MAX_HEIGHT>
        inline void skip_list<T, K, MAX_HEIGHT>::insert(const T& element)
        {
                K key = get_key_function(element);
                ptr new_node = ptr( new node(*this, element) );
                int level = new_node->height;
                ptr current = this->beginning;
                ptr next;
                while (level >= 0)
                {
                        next = current->neighbours[level];

                        while (next->get_key() < key)
                        {
                                current = next;
                                next = next->neighbours[level];
                        }
                        current->neighbours[level] = new_node;
                        new_node->neighbours[level] = next;
                        level--;
                }
				size++;
        }


        template<class T, class K, int MAX_HEIGHT>
        inline void skip_list<T, K, MAX_HEIGHT>::insert(T&& element)
        {
                K key = get_key_function(element);
                ptr new_node = ptr(new node(element));
                int level = new_node->height;
                ptr current = this->beginning;
                ptr next;
                while (level >= 0)
                {
                        next = current->neighbours[level];

                        while (key< next->get_key())
                        {
                                current = next;
                                next = next->neighbours[level];
                        }
                        current->neighbours[level] = new_node;
                        new_node->neighbours[level] = next;
                        level--;
                }
				size++;
        }


        template<class T, class K, int MAX_HEIGHT>
        inline std::pair<bool, T> skip_list<T, K, MAX_HEIGHT>::get_element(const K& key)
        {
                ptr current = get_preceeding(key);
                if (get_key_function(current->value) == key) return std::make_pair(true,current->value);
                else return std::make_pair(false, current->value);
        }


        template<class T, class K, int MAX_HEIGHT>
        inline std::pair<bool, T> skip_list<T, K, MAX_HEIGHT>::get_element(K&& key)
        {
                ptr current = get_preceeding(key);
                if (get_key_function(current->value) == key) return std::make_pair(true,current->value);
                else return std::make_pair(false,current->value);

        }


        template<class T, class K, int MAX_HEIGHT>
        inline void skip_list<T, K, MAX_HEIGHT>::remove(const K & key)
        {
                ptr current = this->beginning;
                int level = current->height;
                ptr next = current->neighbours[level];
				bool is_being_deleted = false;
                while (level >= 0)
                {

                        while (next->get_key() < key)
                        {
                                current = next;
                                next = next->neighbours[level];
                        }
                        if (next->get_key() == key)
                        {
								is_being_deleted = true;
                                current->neighbours[level] = next->neighbours[level];
                                next = current;
                                level--;
                        }
                        else
                        {
                                level--;
                                next = current->neighbours[level];
                        }
                }
				if (is_being_deleted)size--;
        }


        template<class T, class K, int MAX_HEIGHT>
        inline void skip_list<T, K, MAX_HEIGHT>::remove(K && key)
        {
                ptr current = this->beginning;
                int level = current->height;
                ptr next = current->neighbours[level];
				bool is_being_deleted = false;
                while (level >= 0)
                {

                        while (next->get_key() < key)
                        {
                                current = next;
                                next = next->neighbours[level];
                        }
                        if (next->get_key() == key)
                        {
								is_being_deleted = true;
                                current->neighbours[level] = next->neighbours[level];
                                next = current;
                                level--;
                        }
                        else
                        {
                                level--;
                                next = current->neighbours[level];
                        }

                }
				if (is_being_deleted)size--;

        }

        template<class T, class K, int MAX_HEIGHT>
        inline void skip_list<T, K, MAX_HEIGHT>::print(size_t from_level)
        {
                for (int level = from_level; level >= 0; level--)
                {
                        auto current = this->beginning;
                        while (current != nullptr)
                        {
                                std::cout << current->value;
                                for (int i = 0; i < 10; i++)
                                {
                                        std::cout << "-";
                                }
                                current = current->neighbours[level];

                        }
                        std::cout << std::endl;
                }
        }

		template<class T, class K, int MAX_HEIGHT>
		inline size_t skip_list<T, K, MAX_HEIGHT>::get_size()
		{
			return this->size;
		}


	

}