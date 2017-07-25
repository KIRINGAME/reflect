
class name_class
{
public:
    typedef function< control*() > allocate_fn_t;

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


	void name_class_control(const std::string& name, const allocate_fn_t& alloc);
    
    template<typename T>
    void name_class_control(const std::string& name)
    {
        name_class_control(name, &allocate_fn<T>::allocate);
    }

	control* create_control_by_name(const std::string& name);
};

void name_class::name_class_control(const string& name, const allocate_fn_t& alloc)
{
	name_class_data& n_c_d = m_name_class[name];
	n_c_d.m_alloc = alloc;
}


control* name_class::create_control_by_name(const string& name)
{
	name_class_map::iterator i = m_name_class.find(name);
	if (i == m_name_class.end())
	{
		return 0;
	}
	control* pCtrl = i->second.m_alloc();

	return pCtrl;
}

name_class _g_name_class;
name_class * g_name_class = &_g_name_class;

extern name_class * g_name_class ;
