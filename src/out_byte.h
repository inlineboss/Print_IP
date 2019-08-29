#ifndef OUT_BYTE_H_
#define OUT_BYTE_H_

#include <iostream>
#include <bitset>
#include "usr_type_traits.h"
#include <type_traits>

/*
 * \brief Функция печати ip-адреса для целочисленных типов
 *
 * \tparam Integral - Целочисленный тип
 * \param value - Значение, передаваемое в функцию
 */
template <
        class Integral,
        std::enable_if_t<
				std::is_integral<Integral>::value,
				int
			> = 0
>
auto print_ip(const Integral& value){

	std::bitset<8*sizeof(Integral)> bit(value);

    auto end = sizeof(Integral)-1;
    for(int i = 0; i < end; ++i)
    {
        std::cout<<std::bitset<8>(bit.to_string(),8*i,8).to_ulong()<<".";
    }
    std::cout<<std::bitset<8>(bit.to_string(), 8*end,8).to_ulong()<<std::endl;
}

/*
 * \brief Функция печати ip-адреса для контейнера
 *
 * \tparam Container - Тип контейнера
 * \param value - Значение, передаваемое в функцию
 */
template <
        class Container,
        std::enable_if_t<
			is_container<Container>::value,
			int
		> = 0
>
auto print_ip(const Container& value){
	if constexpr (std::is_same<Container, std::string>::value) {

		std::cout << value;

	} else {

		auto it = value.begin();
		auto inc_end = --value.end();

		for(; it != inc_end; ++it){
			std::cout << *it << ".";
		}
		std::cout << *it;
	}

	std::cout << std::endl;
}

/*
 * \brief Функция печати ip-адреса для кортежа
 *
 * \tparam Tuple - Тип кортежа
 * \param value - Значение, передаваемое в функцию
 */
template<typename Tuple, std::size_t... It>
void print_ip_tuple(const Tuple& value, std::index_sequence<It...>){
	((std::cout << (It == 0 ? "" : ".") << std::get<It>(value)), ...) << "\n";
}

/*
 * \brief Функция печати ip-адреса для кортежа
 *
 * \tparam Tuple - Тип кортежа
 * \param value - Значение, передаваемое в функцию
 */
template<typename T, std::enable_if_t<is_valid_tuple<T>::value, int> = 0>
auto print_ip(const T& obj){
	print_ip_tuple(obj,  std::make_index_sequence<std::tuple_size<T>::value>{});
}



#endif /* OUT_BYTE_H_ */
