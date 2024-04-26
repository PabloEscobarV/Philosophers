/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:54:13 by polenyc           #+#    #+#             */
/*   Updated: 2024/04/26 14:35:17 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

class	Alkash
{
	long	buchat;
public:
	Alkash(long _buchat = 0);
	Alkash(const Alkash& obj);
	~Alkash();
	Alkash&	operator=(const Alkash& obj);
	void	getBuchlo(Buchlo& buchlo, mutex& mt);
};

class	Buchlo
{
	int	id;
public:
	Buchlo();
	Buchlo(const Buchlo& obj);
	~Buchlo();
	Buchlo&	operator=(const Buchlo& obj);
	void	set_id(int _id = 0);
	int		get_id();
	friend ostream&	operator<<(ostream& os, const Buchlo& obj);
};