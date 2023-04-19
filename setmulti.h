#ifndef SET_MULTI__H
#define SET_MULTI__H

#include<map>
#include<set>

template<typename T>
class set_multi_util{
    private:

        typedef std::map<T,int> m_set;

        m_set m;
        std::set<T>& set;

        typedef typename std::set<T>::iterator set_it;
        typedef typename std::set<T>::const_iterator set_cit;

        typedef typename m_set::iterator m_set_it;
        typedef typename m_set::const_iterator m_set_cit;

    public:
        set_multi_util() = default;

        set_multi_util(std::set<T> &_set):set(_set){
            for (set_it it = _set.begin(); it != _set.end(); it++)
            {
                m.insert({*it,1});
            }            
        }

        void insert(T e){
            
            if(m.find(e)!=m.end()){
                int countAppearance = m.find(e)->second;
                m.erase(e);
                m.insert({e,countAppearance+1});
                
            }else{
                set.insert(e);
                m.insert({e,1});
            }
            
        }
        
        int size(){ 
            int size=0;
            for (m_set_it it = m.begin(); it != m.end(); it++)
            {
                size=size+it->second;
            }
            return size;
        }

        int count(T e) const {
            int count=0;
            for (m_set_cit it = m.begin(); it != m.end(); it++)
            {
                if(it->first==e){
                    count=it->second;
                }
            }
            return count;
        }

        void erase(T e){
            for (m_set_it it = m.begin(); it != m.end(); it++)
            {
                if(it->first==e){
                    m.erase(it);
                    break;
                }
            }
            for (set_it it = set.begin(); it != set.end(); it++)
            {
                if(*it==e){
                    set.erase(it);
                    break;
                }
            }

        }

        void erase (set_it first){
            T e;
            for (set_it it = set.begin(); it != set.end(); it++){
                if(it==first){
                    e=*it;
                    set.erase(it);
                    for (m_set_it it2 = m.begin(); it2 != m.end(); it2++){
                        if(it2->first==e){
                            m.erase(it2);
                            break;
                        }
                    }
                    break;
                }
            }
            
        }

        void erase(set_it _first,set_it _last) {
             m_set_it it1;
             m_set_it it2;
             bool intervalBegun=false;
             for (m_set_it it = m.begin(); it != m.end(); it++){
                if(it->first==*_first){
                    it1=it;
                    intervalBegun=true;

                }
                if(it->first==*_last && intervalBegun==true){
                    it2=it;
                    break;
                }
            }
            m.erase(it1,it2);
            set.erase(_first,_last);

        }

        void erase_one_element(T e){
            for (m_set_it it = m.begin(); it != m.end(); it++)
            {
                if(it->first==e){
                    if(it->second>1){
                        int count=it->second;
                        m.erase(it);
                        m.insert({e,count-1});
                    }else{
                        m.erase(it);
                        for (set_it it_set = set.begin(); it_set != set.end(); it_set++){
                            if((*it_set)==e){
                                set.erase(it_set);
                                break;
                            }

                        }
                    }
                    break;
                }
            }
        }

};


#endif