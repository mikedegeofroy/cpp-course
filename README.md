# Taking a C++ course in University

> **Disclaimer:**
> 1) **I'm doing this to learn and make content for my portfolio.** The code in here will probably be messy, and I will slowly but surely rewrite most of it. So make sure to read the readme's in the sub-folders to keep up with any changes. 
> 2) This repo contains the labworks as I submitted them to my teachers / mentors. I will work on them to make them better, so make sure to see the commit history and read the readme's. 
> 3) This is a **work in progress**, so be patient, I posted all the code, but it will take time to review and comment it. 

## Prelogue

Before taking this course in my first year at ITMO University, I was already quite familiar with code. At this point I've done multiple small projects, mostly in the frontend feild (javascript and it's frameworks). I was familiar with C++, but never actually dove deep into it, since it's hard to implement in real world situations, unless you're already quite experienced.

It's safe to say, that at this point I was quite familiar with the unix environement, understood quite well the workings of my machine, and was good at using the cli (Terminal).

# Labwork 1

## Assignment 

Make a "word coutner" utility for text files. This cli utility should support the following commands:

-l, --lines outputs only the number of lines
-c, --bytes outputs the size of the file in bytes
-w, --words outputs the count of words
-m, --chars outputs the number of characters

This is my first ever labwork, and it's fairly straight and simple, I knew really nothing about c++ programming other than the syntax, but this would become a core stepping stone for me falling in love with C++. Now I love C++ for being very basic, blazing fast and me having complete control on how to handle garbage collection and data allocation. But I knew nothing back then, so naive. Anways, I gave it my best, even making a nice readme.md file for the project with animations and everything. 

In fact, the code is okay at best, but I'm trying to find time to review it and make it better, so if you ever use this code base as an example you don't end up making the same mistakes as I did.

## Result

Here's the [result](/cpp-labwork-1).

![](https://s4.gifyu.com/images/demoecd70c91f2089499.gif)

## Comments

I'm pretty sure that this cli doesn't work exactly in the most efficient way, mostly because of my (then) partial understanding how ascii is encoded and what the hell is my pointer doing in the stream.

# Labwork 2

## Assignment

Create a uint32_t (unsigned int 32) type. This type has to support implicit conversions from string, sums, substractions, multiplications, output to console, !=, == operators and division. 

## Result

## Comments 

I have to review the way I wrote this labwork, I remember being very tight on time and not really understanding what they wanted for me, it was also around that time that I started to understand how types worked and what implicit and explicit casting was. 

# Labwork 10

Now this is the second semester, and I'm running late on my C++ course, because of some hickups with my math classes. I was about to fail, so I needed something **big**. I remember working on this project non stop for over 30h. This one had to be perfect. This is a labwork that gave me a chance at showing my creativity and my understanding of code, since we where for the first time allowed to use libraries. I remember having a spreadsheet with different features I wanted to add, and one by one ticking the "completed" checkmark and having my progress bar getting ever cloaser to 100%.

Anyways, before university I spent most of my time being a script kitty. I used to literally open node.js, get 2 cool libraries I liked, join them, and make them into some fun toy I would play around with for a couple of days, and then throw away, since it was too much of a pain in the ass to mantain. But anyways, here's the idea I had.

1) Clickable Interface
  I was using htop one day, until, by accident, I clicked on a button, and to my surprise, it actually worked, so I got very curious on how the hell they where doing that?

2) Map
  I wanted to add a map of the city you're looking at, I thought that would be exactly the overkill idea that would be perfect for a high grade. 

3) Good Structure
  I sucked at file structure and OOP at this point, so I wanted to make a project, that would have a smart structure so I can support it later, also to make a good impression.

![](/content/labwork-12-showcase.gif)
