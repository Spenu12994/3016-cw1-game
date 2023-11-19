<h1>Welcome To The Game!</h1>


A Demon Acolayde has risen from the earth and threatens the peaceful valley village.
it is your goal to:
traverse through the dangerous forest,
defeat foes,
level up,
and become strong enough to defeat the demon acolayde.
<h3>GitHub Repository: </h3> https://github.com/Spenu12994/3016-cw1-game.git<br>
<h3>Youtube Link: </h3>
https://youtu.be/clwTpAEhh74<br>

<h2>Controls:</h2>
<ul>
<li>wasd - Movement</li>
<li>e,f,enter - accept</li>
<li>c - save and close the game</li>
</ul>

(Name Your character "Dev" to skip the intro cutscene)

<h2>Gameplay:</h2>

<h3>Freeroam -</h3>
Explore the open world using the WASD keys,
search for powerful crystals (p) to aid in your growth,
search through tall grass (M) to chance encounter dangerous enemies lurking through the reeds,
and use health stations (H) to recover from close victories.

<h3>Combat - When roaming tall grass you might encounter enemies... -</h3>
use A and D to navigate the menu (and e,f,or Enter to select) to choose between 3 Battle options:
[
<h4>Fight -</h4> 
	Attack an enemy,
	With precise swings you can hit critical points and deal additional damage to enemies!,
	when arrows appear on screen, use WASD or Arrow Keys to press in the same direction,
	successful swings will increase a multiplier that gets added to your final attack to deal bonus damage.

<h4>Special -</h4> 
	With your training and expertise, you can predict or immobilise enemies with ease,
	when activating your special, you will either decrease the enemy's attack power, or speed
	leaving them weakened to further attacks

<h4>Run -</h4> 	
	Sometimes a battle can be too much,
	by hitting run you can quickly flee the battle and recouperate health in order to try again.
	Be warned however, Some enemies will trap you on the battlefield leaving you unable to run,
	and wasting a turn trying to scurry.
]

Finishing a battle will reward you with EXP proportionate to the enemy's level, and Level up your Character.

<h3>Stats -</h3>

Every Creature in the shallow valley has 3 main stats:
{
<h4>Health -</h4> 
	the Hit Points a character has, decrease with successful attacks against them.
	if a creature's hitpoints are reduced to zero they are defeated!
	if this creature is you however...you will fail, being sent back to your most recent save.
<h4>Speed -</h4>
	A Creature's speed defines how swift it is in combat
	The Higher a creature's speed, the more likely it is to dodge incoming attacks.
<h4>Attack -</h4>
	The power of a creature's attack, dealing more damage to your hitPoints the higher the attack is.
}

These Stats increase as you level up, but the same is true for your enemies...
<hr>

<h1>Testing :</h1>
Health less than 10% creates low health char:<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/514b9561-0213-4128-a84b-49bb49d35ff8)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/c233cc70-a755-4068-9f98-397738960503)<br>

<h2>Deleting the Save data txt file:</h2><br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/0c4a5e53-1683-47c3-9bee-ed5048b587fb)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/152db37f-e129-4536-be4f-581a736d211f)<br>

Running the program causes it to return -1, however write a new Save.txt File<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/f60940da-e450-4567-9221-3fba6c416442)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/15b6a937-1090-4767-99e4-567156027425)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/4dc883a7-c0cc-43b0-b125-5c1e61dbc787)<br>

<h2>Pressing Continue without making a new save:</h2><br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/5c5ff207-2b4f-44b8-92eb-a96637c27598)<br>
Asks for name and starts game as if the player hit "New Game"<br>

<h2>Creating a save after levelling up:</h2><br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/becb71ba-c0f2-4cc8-b07a-5c7ab6bff210)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/23eb242d-7c98-4778-8905-283c2fcc7e23)<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/8455fb9a-b45f-44b8-8351-7ba5a32234fe)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/3eed4d1f-c4ce-4786-a8bf-6a29f918ee1d)<br>

<h2>Does starting a new game reset save:</h2><br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/0ff1f7a4-b4bf-43a2-ae56-70093b47b461)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/c0a619ab-a4b2-461d-8e9c-3597d9b5fd97)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/d809ecba-852d-41db-a566-cbad667bf765)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/d4a6636d-6190-43f2-aa62-eff9780dcab0)<br>

 <h2>Test Cases</h2>
<h3>Load Save State</h3>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/3860f2d4-7a32-4f8c-afc1-429d1f42a2d0)<br>

This Section of code (as commented) tries to open our save file, however throws an exception when the file is missing, or if any other error occurs, resetting the file and writing a new one.

<h3>Set Name</h3>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/5822c7ab-2c43-41fe-858f-6403cb674e63)<br>

This block displays the "setName" method belonging to our player class that setr our user's name.<br>
Using try catch blocks, throws, and error exception handling, we can ensure that the name chosen is an appropriate length and doesn't contain any impossible/imparsable characters.<br>

<h1>Additional Details</h1>
<h2>Saves</h2>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/4fddb60a-0026-40ac-9070-44c56b663f22)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/1cf35b94-5bf7-4695-ae4c-5882c3056fc2)<br>
our save file is stored in the above format, and is read through, extracted into an array, and used to create a Savestate Class as seen in the images below...<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/844d8eb5-13ac-448e-9e4c-65ab86300927)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/84c06356-ba76-49a4-9a23-b4edfed10325)<br>

<h2>Class Hierarchy</h2>
Game and Save have no hierarchy as they do not need any children or parents...<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/22568f68-1065-4a09-9a0e-7ea26b00231d)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/d4d04ce0-c7d1-4ace-b077-e08debf7c8fd)<br>

Our Player and Enemies, however, have a long hierarchy to abstract as much common code as possible.<br> 
We use a mix of single inheritance and multiple inheritance in order to achieve this.<br>

We Start With the Fighter Class:<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/11037768-ed8f-467a-b689-eb76c62f078c)<br>

Inheriting from fighter we have Player and Enemy Classes:<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/854be00d-1a33-4978-907a-2f234db8b2a7)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/f287340c-17d9-4ad4-b1b1-a1ec140a6d23)<br>

Then Inheriting from Enemy we have our Beast, Humanoid, And Demon Enemy types:<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/1ba4983b-cc24-41e9-96d6-ce1d3468a6b1)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/4b39db3d-7ab5-4789-bb29-c88910c56c1f)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/215f2caf-abfe-423a-b935-ce8e1a67fe56)<br>

And then inheriting from those we have our different enemies:<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/b017b83a-4a59-44d4-b6ce-6a6c18bcc76e)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/66ab50ac-7064-4a09-9036-b3933a7bdccc)<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/92f2774d-f7a0-4e6d-8b9b-f12190e41d1d)<br>

This class layout means that if we wanted to add another enemy, or enemy type, it would be as simple as just creating a new class,<br>
The Demonite and Demon classes were added late in production when deciding on what the boss should be, but if we wanted to make a new enemy such as a sea monster all we would need is the following sections:<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/c615dc74-e185-451e-9d12-09083bc54646)<br>


In the above code we have added a new enemy type (Amphibian) and two new monsters (Lake Monster and Monsterous Toad)<br>
This Enemy Type comes with its own Type and each enemy has a different set of stats (speed, attack, health) based on its assumed capability (The Toad is slow and string, the lake monster is quick but weak)<br>
By utilising virtual functions, our specialType() text for both of them will display an amphibian related message<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/0499e8f6-4532-40d0-af13-d71003ae03fe)<br>

And the toad even uses virtual functions to have its own unique Idle() text<br>
![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/7c32da05-a128-4c91-9231-cb63c4ed9e50)<br>

<h3>Uml for our Class Hierarchy would look like this: </h3>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/5fb281b5-396b-4637-a7b2-154ed6073aad)<br>

And this layout makes other adjustments possible, such as adding new Enemy types, New enemies, and New Fighter types too, greatly aiding future development:<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/1e3e84ad-8390-49dd-92bf-4d35ec61f0fa)<br>

Larger Text:<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/767e527b-44d8-4ab0-939f-4dfe5b968e46)<br>

<h2>Early UML Diagrams: </h2>

<h3>Entity Relationship Diagram:</h3>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/254a76f6-8ec0-4fea-9853-9b8648615888)<br>

This version was the original plan for the class structure and relationships, however during production I found that some bits needed to be changed:<br>
<ul>
	<li>Player and Enemy shared various methods and stats that could be abstracted further into a Fighter Class (such as attacking, taking damage, health, speed, attack, etc)</li>
	<li>The Level class was not doing enough to be justified as its own class, and so it was tweaked into the save class, which handles getting our files like the level class, however also handles saving and loading our game</li>
	<li>Due to the scope of the project, the final enemy count was scaled down to just 3 enemies for each enemy type, as otherwise it would be too many different items to explain quickly</li>
	<li>The Addition of the Fight class to handle the combat turns was not an expected addition in early development, as the final "Fighting" gameplay was undecided</li>
</ul><br>

A more accurate final ERD would likely look like the following:<br>

![image](https://github.com/Spenu12994/3016-cw1-game/assets/91668500/8bf6500b-de19-4345-a681-9491e18dc914)<br>


