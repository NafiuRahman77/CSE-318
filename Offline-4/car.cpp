#include<iostream>
#include"car.hpp"

Car::Car(){
  
}
void Car::map_to_int(){
  for(int i=0;i<6;i++){
    own_attribute_values.push_back(d.attribute_value_mapper[i].at(attribute_values_string[i]));
   // std::cout<<d.attribute_value_mapper[i].at(attribute_values_string[i])<<" ";
  }
  //std::cout<<std::endl;
  verdict=d.verdict_name_mapper[verdict_string];
}