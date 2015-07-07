#pragma once

#include <cstddef>
#include <iosfwd>
#include "traits_internal.h"
#include "__addressof.h"
#include "container_traits.h"

namespace Yupei
{
	/*
	iterator synopsis

	namespace std
	{

	template<class Iterator>
	struct iterator_traits
	{
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef random_access_iterator_tag iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct iterator
	{
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
	};

	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// extension: second argument not conforming to C++03
	template <class InputIterator>
	void advance(InputIterator& i,
	typename iterator_traits<InputIterator>::difference_type n);

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last);

	template <class Iterator>
	class reverse_iterator
	: public iterator<typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference>
	{
	protected:
	Iterator current;
	public:
	typedef Iterator                                            iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::reference       reference;
	typedef typename iterator_traits<Iterator>::pointer         pointer;

	reverse_iterator();
	explicit reverse_iterator(Iterator x);
	template <class U> reverse_iterator(const reverse_iterator<U>& u);
	Iterator base() const;
	reference operator*() const;
	pointer   operator->() const;
	reverse_iterator& operator++();
	reverse_iterator  operator++(int);
	reverse_iterator& operator--();
	reverse_iterator  operator--(int);
	reverse_iterator  operator+ (difference_type n) const;
	reverse_iterator& operator+=(difference_type n);
	reverse_iterator  operator- (difference_type n) const;
	reverse_iterator& operator-=(difference_type n);
	reference         operator[](difference_type n) const;
	};

	template <class Iterator1, class Iterator2>
	bool
	operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator1, class Iterator2>
	bool
	operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator1, class Iterator2>
	bool
	operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator1, class Iterator2>
	bool
	operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator1, class Iterator2>
	bool
	operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator1, class Iterator2>
	bool
	operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x);

	template <class Iterator> reverse_iterator<Iterator> make_reverse_iterator(Iterator i); // C++14

	template <class Container>
	class back_insert_iterator
	{
	protected:
	Container* container;
	public:
	typedef Container                   container_type;
	typedef void                        value_type;
	typedef void                        difference_type;
	typedef back_insert_iterator<Cont>& reference;
	typedef void                        pointer;

	explicit back_insert_iterator(Container& x);
	back_insert_iterator& operator=(const typename Container::value_type& value);
	back_insert_iterator& operator*();
	back_insert_iterator& operator++();
	back_insert_iterator  operator++(int);
	};

	template <class Container> back_insert_iterator<Container> back_inserter(Container& x);

	template <class Container>
	class front_insert_iterator
	{
	protected:
	Container* container;
	public:
	typedef Container                    container_type;
	typedef void                         value_type;
	typedef void                         difference_type;
	typedef front_insert_iterator<Cont>& reference;
	typedef void                         pointer;

	explicit front_insert_iterator(Container& x);
	front_insert_iterator& operator=(const typename Container::value_type& value);
	front_insert_iterator& operator*();
	front_insert_iterator& operator++();
	front_insert_iterator  operator++(int);
	};

	template <class Container> front_insert_iterator<Container> front_inserter(Container& x);

	template <class Container>
	class insert_iterator
	{
	protected:
	Container* container;
	typename Container::iterator iter;
	public:
	typedef Container              container_type;
	typedef void                   value_type;
	typedef void                   difference_type;
	typedef insert_iterator<Cont>& reference;
	typedef void                   pointer;

	insert_iterator(Container& x, typename Container::iterator i);
	insert_iterator& operator=(const typename Container::value_type& value);
	insert_iterator& operator*();
	insert_iterator& operator++();
	insert_iterator& operator++(int);
	};

	template <class Container, class Iterator>
	insert_iterator<Container> inserter(Container& x, Iterator i);

	template <class T, class charT = char, class traits = char_traits<charT>, class Distance = ptrdiff_t>
	class istream_iterator
	: public iterator<input_iterator_tag, T, Distance, const T*, const T&>
	{
	public:
	typedef charT char_type;
	typedef traits traits_type;
	typedef basic_istream<charT,traits> istream_type;

	constexpr istream_iterator();
	istream_iterator(istream_type& s);
	istream_iterator(const istream_iterator& x);
	~istream_iterator();

	const T& operator*() const;
	const T* operator->() const;
	istream_iterator& operator++();
	istream_iterator  operator++(int);
	};

	template <class T, class charT, class traits, class Distance>
	bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
	const istream_iterator<T,charT,traits,Distance>& y);
	template <class T, class charT, class traits, class Distance>
	bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
	const istream_iterator<T,charT,traits,Distance>& y);

	template <class T, class charT = char, class traits = char_traits<charT> >
	class ostream_iterator
	: public iterator<output_iterator_tag, void, void, void ,void>
	{
	public:
	typedef charT char_type;
	typedef traits traits_type;
	typedef basic_ostream<charT,traits> ostream_type;

	ostream_iterator(ostream_type& s);
	ostream_iterator(ostream_type& s, const charT* delimiter);
	ostream_iterator(const ostream_iterator& x);
	~ostream_iterator();
	ostream_iterator& operator=(const T& value);

	ostream_iterator& operator*();
	ostream_iterator& operator++();
	ostream_iterator& operator++(int);
	};

	template<class charT, class traits = char_traits<charT> >
	class istreambuf_iterator
	: public iterator<input_iterator_tag, charT,
	typename traits::off_type, unspecified,
	charT>
	{
	public:
	typedef charT                         char_type;
	typedef traits                        traits_type;
	typedef typename traits::int_type     int_type;
	typedef basic_streambuf<charT,traits> streambuf_type;
	typedef basic_istream<charT,traits>   istream_type;

	istreambuf_iterator() noexcept;
	istreambuf_iterator(istream_type& s) noexcept;
	istreambuf_iterator(streambuf_type* s) noexcept;
	istreambuf_iterator(a-private-type) noexcept;

	charT                operator*() const;
	pointer operator->() const;
	istreambuf_iterator& operator++();
	a-private-type       operator++(int);

	bool equal(const istreambuf_iterator& b) const;
	};

	template <class charT, class traits>
	bool operator==(const istreambuf_iterator<charT,traits>& a,
	const istreambuf_iterator<charT,traits>& b);
	template <class charT, class traits>
	bool operator!=(const istreambuf_iterator<charT,traits>& a,
	const istreambuf_iterator<charT,traits>& b);

	template <class charT, class traits = char_traits<charT> >
	class ostreambuf_iterator
	: public iterator<output_iterator_tag, void, void, void, void>
	{
	public:
	typedef charT                         char_type;
	typedef traits                        traits_type;
	typedef basic_streambuf<charT,traits> streambuf_type;
	typedef basic_ostream<charT,traits>   ostream_type;

	ostreambuf_iterator(ostream_type& s) noexcept;
	ostreambuf_iterator(streambuf_type* s) noexcept;
	ostreambuf_iterator& operator=(charT c);
	ostreambuf_iterator& operator*();
	ostreambuf_iterator& operator++();
	ostreambuf_iterator& operator++(int);
	bool failed() const noexcept;
	};

	template <class C> auto begin(C& c) -> decltype(c.begin());
	template <class C> auto begin(const C& c) -> decltype(c.begin());
	template <class C> auto end(C& c) -> decltype(c.end());
	template <class C> auto end(const C& c) -> decltype(c.end());
	template <class T, size_t N> T* begin(T (&array)[N]);
	template <class T, size_t N> T* end(T (&array)[N]);

	template <class C> auto cbegin(const C& c) -> decltype(std::begin(c));        // C++14
	template <class C> auto cend(const C& c) -> decltype(std::end(c));            // C++14
	template <class C> auto rbegin(C& c) -> decltype(c.rbegin());                 // C++14
	template <class C> auto rbegin(const C& c) -> decltype(c.rbegin());           // C++14
	template <class C> auto rend(C& c) -> decltype(c.rend());                     // C++14
	template <class C> auto rend(const C& c) -> decltype(c.rend());               // C++14
	template <class E> reverse_iterator<const E*> rbegin(initializer_list<E> il); // C++14
	template <class E> reverse_iterator<const E*> rend(initializer_list<E> il);   // C++14
	template <class T, size_t N> reverse_iterator<T*> rbegin(T (&array)[N]);      // C++14
	template <class T, size_t N> reverse_iterator<T*> rend(T (&array)[N]);        // C++14
	template <class C> auto crbegin(const C& c) -> decltype(std::rbegin(c));      // C++14
	template <class C> auto crend(const C& c) -> decltype(std::rend(c));          // C++14

	// 24.8, container access:
	template <class C> constexpr auto size(const C& c) -> decltype(c.size());         // C++17
	template <class T, size_t N> constexpr size_t size(const T (&array)[N]) noexcept; // C++17
	template <class C> constexpr auto empty(const C& c) -> decltype(c.empty());       // C++17
	template <class T, size_t N> constexpr bool empty(const T (&array)[N]) noexcept;  // C++17
	template <class E> constexpr bool empty(initializer_list<E> il) noexcept;         // C++17
	template <class C> constexpr auto data(C& c) -> decltype(c.data());               // C++17
	template <class C> constexpr auto data(const C& c) -> decltype(c.data());         // C++17
	template <class T, size_t N> constexpr T* data(T (&array)[N]) noexcept;           // C++17
	template <class E> constexpr const E* data(initializer_list<E> il) noexcept;      // C++17

	}  // std

	*/

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };


	namespace Internal
	{
		

		template<
			typename Iterator,
			bool IsIterator>
		struct iterator_traits_impl;

		template<
			typename Iterator
		>
		struct iterator_traits_impl<Iterator, true>
		{
			using difference_type = typename Iterator::difference_type;
			using value_type = typename Iterator::value_type;
			using pointer = typename Iterator::pointer;
			using reference = typename Iterator::value_type;
			using iterator_category = typename Iterator::value_type;
		};

		template<
			typename Iterator,
			typename = void
		>
		struct is_iterator : false_type
		{

		};

		template<
			typename Iterator,
			typename = void_t<
			typename Iterator::value_type,
			typename Iterator::difference_type,
			typename Iterator::reference,
			typename Iterator::pointer,
			typename Iterator::iterator_category
			>>
		struct is_iterator : true_type
		{

		};
	}

	template<class Iterator> 
	struct iterator_traits : Internal::iterator_traits_impl<Iterator,
		Internal::is_iterator<Iterator>::value>
	{

	};

	template<class T> 
	struct iterator_traits<T*> 
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class T> 
	struct iterator_traits<const T*> 
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<typename Iterator>
	using value_t = typename iterator_traits<Iterator>::value_type;

	template<typename Iterator>
	using difference_t = typename iterator_traits<Iterator>::difference_type;

	template<typename Iterator>
	using pointer_t = typename iterator_traits<Iterator>::pointer;

	template<typename Iterator>
	using reference_t = typename iterator_traits<Iterator>::reference_type;

	template<typename Iterator>
	using iterator_category_t = typename iterator_traits<Iterator>::iterator_category;

	template<class Category, class T, class Distance = std::ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct iterator 
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	namespace Internal
	{
		template <class InputIterator, class Distance>
		void advance_impl(InputIterator& i, Distance n,random_access_iterator_tag)
		{
			i += n;
		}

		template <class InputIterator, class Distance>
		void advance_impl(InputIterator& i, Distance n, input_iterator_tag)
		{
			for (;n > 0;--n)
			{
				++i;
			}
		}

		template <class InputIterator, class Distance>
		void advance_impl(InputIterator& i, Distance n, bidirectional_iterator_tag)
		{
			if (n > 0)
			{
				for (;n > 0;--n)
				{
					++i;
				}
			}
			else
			{
				for (;n != 0; ++n)
				{
					--i;
				}
			}
		}
	}

	template <class InputIterator, class Distance>
	void advance(InputIterator& i, Distance n)
	{
		return Internal::advance_impl(i, n, iterator_category_t<InputIterator>{});
	}

	namespace Internal
	{
		template <class InputIterator>
		difference_t<InputIterator> distance_impl(InputIterator first, InputIterator last, input_iterator_tag)
		{
			difference_t<InputIterator> res{};
			for (;first != last;++first)
				++res;
			return res;
		}

		template <class InputIterator>
		difference_t<InputIterator> distance_impl(InputIterator first, InputIterator last, random_access_iterator_tag)
		{
			return last - first;
		}
	}
	
	template <class InputIterator>
	difference_t<InputIterator> distance(InputIterator first, InputIterator last)
	{
		return Internal::distance_impl(first, last, iterator_category_t<InputIterator>{});
	}
	template <class ForwardIterator>
	ForwardIterator next(ForwardIterator x,
		difference_t<ForwardIterator> n = 1)
	{
		Yupei::advance(x, n);
		return x;
	}
	 template <class BidirectionalIterator>
	 BidirectionalIterator prev(BidirectionalIterator x,
		 difference_t<BidirectionalIterator> n = 1)
	 {
		 Yupei::advance(x, -n);
		 return x;
	 }

	 template <class Iterator>
	 class reverse_iterator 
	 {
	 public:
		 using iterator_type = Iterator;
		 using iterator_category = iterator_category_t<Iterator>;
		 using value_type = value_t<Iterator>;
		 using difference_type = difference_t<Iterator>;
		 using pointer = pointer_t<Iterator>;
		 using reference = reference_t<Iterator>;
		 reverse_iterator()
			 :current()
		 {

		 }
		 explicit reverse_iterator(Iterator x)
			 :current(x)
		 {

		 }
		 template <class U> 
		 reverse_iterator(const reverse_iterator<U>& u)
			 :current(u.current)
		 {

		 }
		 template <class U> 
		 reverse_iterator& operator=(const reverse_iterator<U>& u)
		 {
			 current = u.base();
			 return *this;
		 }
		 Iterator base() const // explicit
		 {
			 return current;
		 }
		 reference operator*() const
		 {
			 auto tmp = current;
			 return *--tmp;
		 }
		 pointer operator->() const
		 {
			 return Yupei::addressof(operator*());
		 }
		 reverse_iterator& operator++()
		 {
			 --current;
			 return *this;
		 }
		 reverse_iterator operator++(int)
		 {
			 auto tmp = current;
			 --current;
			 return *tmp;
		 }
		 reverse_iterator& operator--()
		 {
			 ++current;
			 return *this;
		 }
		 reverse_iterator operator--(int)
		 {
			 auto tmp = *this;
			 ++current;
			 return tmp;
		 }
		 reverse_iterator operator+ (difference_type n) const
		 {
			 return reverse_iterator(current - n);
		 }
		 reverse_iterator operator- (difference_type n) const
		 {
			 return reverse_iterator(current + n);
		 }
		 reverse_iterator& operator-=(difference_type n)
		 {
			 current += n;
			 return *this;
		 }
		 reference operator[](difference_type n) const
		 {
			 return current[-n - 1];
		 }
	 protected:
		 Iterator current;
	 };
	 template <class Iterator1, class Iterator2>
	 bool operator==(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y)
	 {
		 return x.current == y.current;
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator<(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y)
	 {
		 return x.current > y.current;
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator!=(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y)
	 {
		 x.current != y.current;
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator>(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y)
	 {
		 return x.current < y.current;
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator>=(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y)
	 {
		 return x.current <= y.current;
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator<=(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y)
	 {
		 x.current >= y.current;
	 }
	 template <class Iterator1, class Iterator2>
	 auto operator-(
		 const reverse_iterator<Iterator1>& x,
		 const reverse_iterator<Iterator2>& y) -> decltype(y.base() - x.base())
	 {
		 return y.current - x.current;
	 }
	 template <class Iterator>
	 reverse_iterator<Iterator> operator+(
		 difference_t<Iterator> n,
		 const reverse_iterator<Iterator>& x)
	 {
		 return reverse_iterator<Iterator>(x.current - n);
	 }
	 template <class Iterator>
	 reverse_iterator<Iterator> make_reverse_iterator(Iterator i)
	 {
		 return reverse_iterator<Iterator>(i);
	 }

	 template <class Container>
	 class back_insert_iterator 
	 {
	 protected:
		 Container* container;
	 public:
		 using iterator_category = output_iterator_tag;
		 typedef void value_type;
		 typedef void difference_type;
		 typedef void pointer;
		 typedef void reference;
		 typedef Container container_type;
		 explicit back_insert_iterator(Container& x)
			 :container(Yupei::addressof(x))
		 {

		 }
		 back_insert_iterator& operator=(const container_value_type<Container>& value)
		 {
			 container->push_back(value);
			 return *this;
		 }
		 back_insert_iterator& operator=(value_t<Container>&& value)
		 {
			 container->push_back(Yupei::move(value));
			 return *this;
		 }
		 back_insert_iterator& operator*()
		 {
			 return *this;
		 }
		 back_insert_iterator& operator++()
		 {
			 return *this;
		 }
		 back_insert_iterator operator++(int)
		 {
			 return *this;
		 }
	 };
	 template <class Container>
	 back_insert_iterator<Container> back_inserter(Container& x)
	 {
		 return back_insert_iterator<Container>(x);
	 }

	 template <class Container>
	 class front_insert_iterator {
	 protected:
		 Container* container;
	 public:
		 typedef output_iterator_tag iterator_category;
		 typedef void value_type;
		 typedef void difference_type;
		 typedef void pointer;
		 typedef void reference;
		 typedef Container container_type;
		 explicit front_insert_iterator(Container& x)
			 :container(Yupei::addressof(x))
		 {

		 }
		 front_insert_iterator& operator=(const container_value_type<Container>& value)
		 {
			 container->push_front(value);
		 }
		 front_insert_iterator& operator=(container_value_type<Container>&& value)
		 {
			 container->push_front(Yupei::move(value));
		 }
		 front_insert_iterator& operator*()
		 {
			 return *this;
		 }
		 front_insert_iterator& operator++()
		 {
			 return *this;
		 }
		 front_insert_iterator operator++(int)
		 {
			 return *this;
		 }
	 };

	 template <class Container>
	 class insert_iterator {
	 protected:
		 Container* container;
		 typename Container::iterator iter;
	 public:
		 typedef output_iterator_tag iterator_category;
		 typedef void value_type;
		 typedef void difference_type;
		 typedef void pointer;
		 typedef void reference;
		 typedef Container container_type;
		 insert_iterator(Container& x, container_iterator<Container> i)
			 :container(Yupei::addressof(x)),
			 iter(i)
		 {

		 }
		 insert_iterator& operator=(const container_value_type<Container>& value)
		 {
			 iter = container->insert(iter, value);
			 ++iter;
			 return *this;
		 }
		 insert_iterator& operator=(container_value_type<Container>&& value)
		 {
			 iter = container->insert(iter, Yupei::move(value));
			 ++iter;
			 return *this;
		 }
		 insert_iterator& operator*()
		 {
			 return *this;
		 }
		 insert_iterator& operator++()
		 {
			 return *this;
		 }
		 insert_iterator& operator++(int)
		 {
			 return *this;
		 }
	 };
	 template <class Container>
	 insert_iterator<Container> inserter(Container& x, container_iterator<Container> i)
	 {
		 return insert_iterator<Container>(x, i);
	 }

	 namespace Internal
	 {
		 template<typename Iterator>
		 struct move_iterator_reference_traits
		 {
			 using ref_type = reference_t<Iterator>;
			 using type = Yupei::conditional_t < 
				 is_reference<ref_type>::value,
				 remove_reference_t<ref_type>&&,
				 ref_type> ;
		 };
	 }

	 template <class Iterator>
	 class move_iterator {
	 public:
		 typedef Iterator iterator_type;
		 typedef typename iterator_traits<Iterator>::difference_type difference_type;
		 typedef Iterator pointer;
		 typedef typename iterator_traits<Iterator>::value_type value_type;
		 typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		 using reference = typename Internal::move_iterator_reference_traits<Iterator>::type;
		 move_iterator()
			 :current()
		 {

		 }
		 explicit move_iterator(Iterator i)
			 :current(i)
		 {

		 }
		 template <class U> 
		 move_iterator(const move_iterator<U>& u)
			 :current(u.base())
		 {

		 }
		 template <class U> 
		 move_iterator& operator=(const move_iterator<U>& u)
		 {
			 current = u.base();
			 return *this;
		 }
		 iterator_type base() const
		 {
			 return current;
		 }
		 reference operator*() const
		 {
			 return static_cast<reference>(*current);
		 }
		 pointer operator->() const
		 {
			 return current;
		 }
		 move_iterator& operator++()
		 {
			 ++current;
			 return *this;
		 }
		 move_iterator operator++(int)
		 {
			 auto tmp = *this;
			 ++current;
			 return tmp;
		 }
		 move_iterator& operator--()
		 {
			 --current;
			 return *this;
		 }
		 move_iterator operator--(int)
		 {
			 auto tmp = *this;
			 --current;
			 return tmp;
		 }
		 move_iterator operator+(difference_type n) const
		 {
			 return move_iterator(current + n);
		 }
		 move_iterator& operator+=(difference_type n)
		 {
			 current += n;
			 return *this;
		 }
		 move_iterator operator-(difference_type n) const
		 {
			 return move_iterator(current - n);
		 }
		 move_iterator& operator-=(difference_type n)
		 {
			 current -= n;
			 return *this;
		 }
		 reference operator[](difference_type n) const
		 {
			 return Yupei::move(current[n]);
		 }
	 private:
		 Iterator current; // exposition only
	 };
	 template <class Iterator1, class Iterator2>
	 bool operator==(
		 const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y)
	 {
		 return x.base() == y.base();
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator!=(
		 const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y)
	 {
		 !(x == y);
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator<(
		 const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y)
	 {
		 return x.base() < y.base();
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator<=(
		 const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y)
	 {
		 return !(y < x);
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator>(
		 const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y)
	 {
		 return y < x;
	 }
	 template <class Iterator1, class Iterator2>
	 bool operator>=(
		 const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y)
	 {
		 return !(x < y);
	 }
	 template <class Iterator1, class Iterator2>
	 auto operator-(
		 const move_iterator<Iterator1>& x,
		 const move_iterator<Iterator2>& y) -> decltype(x.base() - y.base())
	 {
		 return x.base() - y.base();
	 }
	 template <class Iterator>
	 move_iterator<Iterator> operator+(
		 typename move_iterator<Iterator>::difference_type n, const move_iterator<Iterator>& x)
	 {
		 return x + n;
	 }
	 template <class Iterator>
	 move_iterator<Iterator> make_move_iterator(Iterator i)
	 {
		 return move_iterator<Iterator>(i);
	 }

	 template <class T, class charT = char, class traits = char_traits<charT>,
	 class Distance = ptrdiff_t>
	 class istream_iterator {
	 public:
		 typedef input_iterator_tag iterator_category;
		 typedef T value_type;
		 typedef Distance difference_type;
		 typedef const T* pointer;
		 typedef const T& reference;
		 typedef charT char_type;
		 typedef traits traits_type;
		 typedef basic_istream<charT, traits> istream_type;
		 see below istream_iterator();
		 istream_iterator(istream_type& s);
		 istream_iterator(const istream_iterator& x) = default;
		 ~istream_iterator() = default;
		 const T& operator*() const;
		 const T* operator->() const;
		 istream_iterator& operator++();
		 istream_iterator operator++(int);
	 private:
		 basic_istream<charT, traits>* in_stream; // exposition only
		 T value; // exposition only
	 };
	 template <class T, class charT, class traits, class Distance>
	 bool operator==(const istream_iterator<T, charT, traits, Distance>& x,
		 const istream_iterator<T, charT, traits, Distance>& y);
	 template <class T, class charT, class traits, class Distance>
	 bool operator!=(const istream_iterator<T, charT, traits, Distance>& x,
		 const istream_iterator<T, charT, traits, Distance>& y);
}
