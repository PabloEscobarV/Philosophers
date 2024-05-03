/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buchlo.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:51 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/03 13:20:39 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

namespace alkashi_sim
{
    Buchlo::Buchlo(int id_) : id(id_)
    {

    }

    Buchlo::Buchlo(const Buchlo& obj)
    {
        id = obj.id;
    }

    Buchlo::~Buchlo()
    {

    }

    Buchlo&	Buchlo::operator=(const Buchlo& obj)
    {
        if (this == &obj)
            return (*this);
        id = obj.id;
        return (*this);
    }

    void	Buchlo::set_id(int _id)
    {
        id = _id;
    }

    int		Buchlo::get_id()
    {
        return (id);
    }

    ostream&	operator<<(ostream& os, const Buchlo& obj)
    {
        os << "BUCHLO ID:\t" << hex << this_thread::get_id() << endl;
        return (os);
    }

    void    Buchlo::lock()
    {
        mt.lock();
    }

    void	Buchlo::unlock()
    {
        mt.unlock();
    }
}
