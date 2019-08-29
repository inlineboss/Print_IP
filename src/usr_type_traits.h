#ifndef USR_TYPE_TRAITS_H_
#define USR_TYPE_TRAITS_H_

#include <tuple>

/**
 * \brief Метафункция определяющая наличие типа итератор
 */
template<typename Target>
struct has_iterator{
private:
	template<typename Cl>
	static constexpr bool get_iter(typename Cl::iterator*) {return true;}

	template<typename Cl>
	static constexpr bool get_iter(...) {return false;}
public:
	static constexpr bool value = get_iter<Target>(nullptr);
};

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
	static constexpr bool value = has_iter<Container>::value;
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
	static constexpr bool value = comparable_type<TypesPack...>::value;
};

/**
 * \brief Метафункция для определения количества типов
 */
template<typename... TypePack>
struct get_size_pack{
private:
	template<std::size_t It, typename... Pack>
	struct type_get{
		static constexpr std::size_t value = It;
	};

	template<std::size_t It, typename T, typename... Pack>
	struct type_get<It, T, Pack...>: type_get<It+1,Pack...>{};

	static constexpr std::size_t star_val = 0;

public:
	static constexpr std::size_t value = type_get<star_val, TypePack...>::value;
};

/**
 * \brief Метафункция для типа кортежа
 * 		  с одинаковым типом данных
 */
template<typename... T>
struct is_valid_tuple{
private:
	template<typename Type>
	struct is_tuple{
		static constexpr bool value = false;
	};

	template<typename Type, typename... Args>
	struct is_tuple<std::tuple<Type, Args...>>:compare_type<Type, Args...> {};

public:
	static constexpr bool value = is_tuple<T...>::value;
};



#endif /* USR_TYPE_TRAITS_H_ */
