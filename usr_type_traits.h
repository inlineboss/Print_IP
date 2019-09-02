#ifndef USR_TYPE_TRAITS_H_
#define USR_TYPE_TRAITS_H_

#include <tuple>

/**
 * \brief Метафункция определения принадлежности к контейнеру
 */
template<typename Container>
struct is_container{
private:
	template<typename...>
	struct voider {
	    using type = void;
	};
	template<class... Ts> using void_t = typename voider<Ts...>::type;


	template<typename Type, typename Enable = void>
	struct has_iter{
		static constexpr bool value = false;
	};

	template<typename Type>
	struct has_iter<Type, void_t<typename Type::iterator>>{
		static constexpr bool value = true;
	};

public:
	static constexpr bool value = has_iter<Container>::value; /**< Результата проверки принадлежности к контейнеру*/
};

/**
 * \brief Метафункция для определения одинаковых типов
 */
template<typename... TypesPack>
struct compare_type{
private:

	template<typename... T>
	struct comparable_type{
		static constexpr bool value = true;
	};

	template<typename T, typename... Pack>
	struct comparable_type<T, T, Pack...>: comparable_type<T, Pack...>{};

	template<typename T, typename U, typename... Pack>
	struct comparable_type<T, U, Pack...>{
		static constexpr bool value = false;
	};

public:
	static constexpr bool value = comparable_type<TypesPack...>::value; /**< Результат сравнения типов */
};

/**
 * \brief Метафункция для определения типа кортежа
 * 		  с одинаковым типом данных
 */
template<typename... T>
struct is_homogen_tuple{
private:
	template<typename Type>
	struct is_tuple{
		static constexpr bool value = false;
	};

	template<typename Type, typename... Args>
	struct is_tuple<std::tuple<Type, Args...>>:compare_type<Type, Args...> {};

public:
	static constexpr bool value = is_tuple<T...>::value; /**< Результат проверки на принадлежность */
};



#endif /* USR_TYPE_TRAITS_H_ */
