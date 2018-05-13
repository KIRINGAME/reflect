#include <function.h>
class name_class
{
private:
	typedef function< base_class*() > allocate_fn_t;

	struct name_class_data
	{
		allocate_fn_t    m_alloc;
	};

	typedef std::map<std::string, name_class_data> name_class_map;
	name_class_map    m_name_class;

	template<typename T>
	struct allocate_fn
	{
		static T* allocate()
		{
			return new T;
		}
	};
	
	void name_class_insert(const std::string& name, const allocate_fn_t& alloc)
	{
		name_class_data& n_c_d = m_name_class[name];
		n_c_d.m_alloc = alloc;
	}
pubilic:
	template<typename T>
	void name_class_insert(const std::string& name)
	{
		name_class_insert(name, &allocate_fn<T>::allocate);
	}

	base_class* create_object_by_name(const std::string& name)
	{
		name_class_map::iterator i = m_name_class.find(name);
		if (i == m_name_class.end())
		{
			return NULL;
		}
		base* pClassT = i->second.m_alloc();

		return pClassT;
	}
};


extern name_class * g_name_class ;
