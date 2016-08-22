//
//  main.cpp
//  water_meter_reader
//
//  Created by Kert Ilm on 22/08/16.
//  Copyright © 2016 Kert Ilm. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <cmath>
int current_data;
int max_data ;
int min_data ;
int last_data;
int average;
int c;
int x;
const int buffer_len = 32;
int rms[buffer_len];
int avg_rms;
bool current_state;
bool last_state;
std::string impulss;
int data[buffer_len];

int count;
int sample = 0;

void print_bool(bool data)
{
	if (data == true)
	{
		std::cout << "high";
	}
	else
	{
		std::cout << "low";
	}
}

void calibration(int data_now)
{
	int rms;
	int avg[buffer_len];
	static int i = 0;
	int f;
	
	data[i] = data_now;
	i++;
	if (i == buffer_len)
	{
		int average_sum = 0;
		for (int x = 0; x < buffer_len; x++)
		{
			average_sum = average_sum + data[x];
		}
		
		int average = average_sum / buffer_len;
		uint64_t rms_sq_sum = 0;
		for(int c = 0; c < buffer_len; c++)
		{
			rms_sq_sum = rms_sq_sum + (data[c] - average)*(data[c] - average);
		}
		
		avg_rms = sqrt(rms_sq_sum/buffer_len);
		
		i = c = x = f =0;
		std::cout << "average rms : " << avg_rms << std::endl;
	}
	
	
}

void calculation(int current_data)
{
	int sample_turn;
	/*if (current_data > max_data)
		{
	 max_data = current_data;
		}
	 
	 if (current_data < min_data)
		{
	 min_data = current_data;
		}
	 
	 if ((current_data > last_data) & (current_data-last_data > (max_data-min_data)/2))
		{
	 current_state = high;
		}
	 
	 if ((current_data < last_data) & ((last_data - current_data) > (max_data-min_data)/2))
		{
	 current_state = low;
		}
	 
	 
		*/
	
	
	if (current_data > avg_rms*1.1)
	{
		current_state = true;
	}
	
	if (current_data < avg_rms*0.9)
	{
		current_state = false;
	}
	
	if (current_state != last_state)
	{
		count++;
	}
	
	last_data = current_data;
	last_state = current_state;
	impulss = count / 2;
	
	
	sample_turn ++;
	if(sample_turn==4)
	{
		calibration(current_data);
		sample_turn=0;
		
		
		
	}
	std::cout << "current state: ";
	print_bool(current_state);
	std::cout << std::endl;
}




int main ()
{
	while (true)
	{
		/* siia ette tuleb lisada see asi,
		 kust ta saab selle current_data
		 */
		current_data = rand() % 100;
		
		if (sample < buffer_len)
		{
			sample++;
			calibration(current_data);
		}
		if (sample == buffer_len)
		{
			calculation(current_data);
		}
		
	}
}
