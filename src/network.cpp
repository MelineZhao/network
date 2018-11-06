#include "network.h"
#include "random.h"
#include <iostream>
#include <utility>

 
		void Network:: resize(const size_t& nodes)
		{ 
			values.clear();
			values.resize(nodes);
			RNG.normal(values, 0,1);
		}
		
		bool Network:: add_link(const size_t& n1, const size_t& n2)
		{		  
			
			 //les liens n'existent pas par défaut
			 bool isn1n2(false);
			 if(n1==n2)
			 {isn1n2=true;}
			 bool link1_2(false);
			 bool link2_1(false);
			 auto values_1=links.equal_range(n1);
			 auto values_2=links.equal_range(n2);
			
			 for(auto i=values_1.first;i!=values_1.second;++i)
				{
					if(i->second==n2)
					{link1_2=true;}
				}
			 for(auto i=values_2.first;i!=values_2.second;++i)
				{
					if(i->second==n1)
					{link2_1=true;}
				}
			 //on assume que n1 et n2 existent
			 bool is_n1(true);
			 bool is_n2(true);
			 //on n'a pas trouvé n1/n2 dans la multimap
			 if(n1<0 or n1>=values.size())
				{is_n1=false;}
			 if(n2<0 or n2>=values.size())
				{ is_n2=false;}
			 if(link1_2==false and link2_1==false and is_n1==true and is_n2==true and isn1n2==false )
				{
						links.insert({n1,n2});
						links.insert({n2,n1});
						return true;
				}	
			else 
				{return false;}
		}
	
		   
		size_t Network:: random_connect(const double& mean_poisson)
		{ 
			int nlink=0;
			for(auto i=links.begin(); i!=links.end(); ++i)
			{
				links.erase(i);
			}
			for (int i=0; i<values.size(); ++i)
			{ 
				int n(RNG.poisson(mean_poisson));
				std::vector <int> nodes(n);
				RNG.uniform_int(nodes,0,values.size()-1);
				for(int j=0; j<nodes.size(); ++j)
				{ 
					add_link(i,nodes[j]);
					{++nlink;}
				 }
			}	
			
			return nlink;
		}
			
		   
		size_t Network:: set_values(const std::vector<double>& new_values)
		{ 
			if(values.size()>new_values.size())
			{ for(size_t i=0; i<new_values.size();++i)
				{ values[i]=new_values[i];}
			}
			
			if(values.size()<new_values.size())
			{ for(size_t i=0; i<values.size();++i)
				{ values[i]=new_values[i];}
			}
			else
			{values=new_values;}
			return values.size();
		}
		
		size_t Network:: size() const
		{ 
			return values.size();
		}
			
		size_t Network:: degree(const size_t &_n) const
		{
			return links.count(_n);
		}
			
			
		double Network:: value(const size_t &_n) const
		{ 
			return values[_n];
		}
			
		std::vector<double> Network:: sorted_values() const
		{
			std::vector<double> descending=values;
			std::sort(descending.begin(), descending.end(), std::greater<double>());
			return descending;
		}
			 
		std::vector<size_t> Network:: neighbors(const size_t& n) const
		{ 	
			std::vector <size_t> neighbors;
			auto bounds=links.equal_range(n);
			for(auto i=bounds.first; i!=bounds.second;++i)
				{ 
					neighbors.push_back(i->second);
				}
			return neighbors;
		}
			
