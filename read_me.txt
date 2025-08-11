Ben Rohman, benrohman3@gmail.com, 7/3/25


Idea is a DND-esque turn-based RPG, various "classes" and "systems" to be
	included
Might add like some magic/abilities n whattnot later on, depends on how helpful stackoverflow feels like 
	being.
Adding some graphics would be cool too

Coded using C++ <3

*** Initial/Rough design:

CLASSES
-------
1. Warrior
	Highest damage reduction
	HP Growth: 19
2. Wizard
	Uses magic
	HP Growth: 9
3. Cleric
	Uses support magic
	HP Growth: 14
4. Rogue
	Highest consistent melee/ranged damage
	HP Growth 14

CLASS LEVELS
------------
Gain stats based on classes
Gain abilities based on level

SHOP SYSTEM
-----------
1. Equipment
2. Consumables

BATTLE SYSTEM
-------------
1. Turn based
2. World levels
3. Different monsters


YOU BITCHES BETTER APPRECIATE THE THOUGHT I PUT INTO THIS SHIT AND IMA EXPLAIN SOME SHIT I THINK IS KINDA COOL

1. There's a character who dies before the story starts named "Hayuma", nicknamed "Yum"(yoom), who was a very 
	happy guy, he died in a really traumatic way and started the story's whole conflict. Here's the 
	meaning behind his name:
	Hayuma (Japanese): "Haru" (spring, light, sun, joy) + "Yume" (dream, vision), I was aiming for 
		something that translated roughly to something like "morningstar". I don't speak Japanese
		but I figured this could be close enough to "dream of light" which had the same vibe.
	
2. There's another character whose name is Velian (spoiler he's the antagonist/anti-villain). His name is also
	cool as fuck so here ya go.
	Velian (Slavic/Ukraine-ish): From either the Slavic name "Velik"(great) or the Ukrainian name "Volya"
		(freedom). I wanted this character's name to be something along the lines of "liberator" and 
		figured I'd have better luck with European names/roots.

	His "villain alias" is going to be "Nulldex" and yes I know that sounds corny as fuck but HEAR ME OUT
		(i.e. let me nerd out at you for a sec and way over shit): It's a combo of "null" and "codex"  
		or "index" (they both work for what I'm getting at)
		
		"Null": In C and C++ and probably other programming languages there are these super cool 
			variables called "pointers" that store the memory address in the computer of 
			another variable's value(explained below). Pointers are conventionally initialized as
			"null" ("NULL" in C and "nullptr" in C++) which is essentially the same as initializing
			a numeric variable as 0. A "null pointer" is a pointer that points to a nonexistent or 
			invalid memory address. If a program tries to use a "null pointer" and use it as if 
			it were pointing at something real then the program will crash and end execution 
			(called a "segmentation fault"/"seg fault" = failure condition raised by hardware with 
			memory protection)
		"Codex": An ancient manuscript text in book form
		"Index": The place/spot something exists in a list or an indicator, sign, or measure of 
			something.
	
	I think that the concept of memory is really interesting and how brains just store all this info. And
		when I was researching everyone's subclasses I read a description of my character, Artificer; 
		Archivist, that was "a USB stick with feelings" and thought that was kinda funny. Archivists 
		are also obsessed with the idea of storing massive amounts of information that can be instantly
		accessible. This gave me the idea for the main storyline and made me decide that I wanted to 
		center the story around memory and memory preservation/loss. And obviously since I'm a bit of 
		a nerd I wanted to include computer memory as well as human memory because I think its kinda 
		really fuckin cool.

* POINTERS: think variable = house, value = valuables in the house, memory address = address of the house, and*
* pointer = piece of paper with the house's address written on it. Pointers let programmers access/modify a   *
* variable through its memory location = handing someone the paper with the house's address on it so that they*
* can go and see what's inside (rob that bitch)								      *
			
* NULL POINTER (same analogy as above): think null pointer = piece of paper with no address on it, a program  *
* trying to use a null pointer as if it were pointing to some real value = trying to go walk into a house that*
* doesn't exist or going to a house you don't know the address/location of (end up lost)		      *
			
