/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:52:11 by vshchuki          #+#    #+#             */
/*   Updated: 2024/06/16 23:30:11 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
using iterFunc =  void (*)(T&);

template <typename T>
void iter(T* arr, int size, iterFunc<T> func)
{
	for (int i = 0; i < size; i++)
	{
		func(arr[i]);
	}
}
