# Lab Exercise: Applying Dependency Inversion Principle in a Simple SFML Game

## Objective:

Refactor the provided SFML application code to implement the Dependency Inversion Principle (DIP) by abstracting the shape rendering process.

## Background:

The Dependency Inversion Principle is a software design guideline that suggests high-level modules should not depend on low-level modules, but both should depend on abstractions. In addition, abstractions should not depend on details, but the details should depend on abstractions. This principle helps in reducing the coupling between the software modules, making the system easier to extend and maintain.

## Initial Code Analysis:

The initial code snippet directly uses sf::CircleShape in the Game class to render a shape on the window. This design tightly couples the Game class to a specific shape type, limiting flexibility and violating DIP. 

`Game` class (High-level) depends on `CircleShape` (low-level). This violates DIP

## Tasks:

1. Define an abstract Shape interface with virtual methods for setting position and color, and for getting the shape to be drawn (sf::Drawble).
2. Create a concrete class that implements this Shape interface, wrapping[^1] an sf::Shape (like sf::CircleShape).
3. Modify the Game class to use the Shape abstraction instead of a concrete sf::CircleShape.
5. If you are struggling with these tasks, checkout the *Hints* section at the end.

## Advanced Task (only attempt after previous tasks complete):

1. Does you `Game` class call methods such as: `shape->setPosition(...)` and ` shape->setColor(...)`? If so, your abstraction maybe depends on details (color & position), violating the DIP. Ask your self "What does the game class *really* want?". It wants the shape to appear different each time. So maybe replace the setPosition & setColor methods with something like `changeAppearance()` and let the shape class figure out how that should be done.

2. Create a Square class that chages size and shape, make the `Game` class draw squares instead of circles **without changing any code in `Game`** 

# Submission

Put all your code into `DIP_worksheet.cpp` and upload this file to the blackboard DIP assignment.


## Hints

### Task 1: Define an Abstract Shape Class (Interface)

What to Do:

Create a general blueprint for shapes in our game. This blueprint is called an interface in programming, and it tells any shape we want to create what functions it must have. For example, all shapes should be able to change their position and color, and we need a way to draw them.

How to Do It:

You will write a class named Shape but with only declarations of functions and no actual code inside them. These functions will be setPosition, setColor, and getDrawable (getDrawable should return a `sf::Drawable&`,  a reference to a `Drawable` object).

Mark these functions as virtual and = 0; to say, "Any shape that follows this blueprint must provide its own version of these functions."

### Task 2: Create a Concrete Class that Implements the Shape Interface

What to Do:

Now, create a specific shape (like a circle) that follows the Shape blueprint you defined. This is called implementing the interface.

How to Do It:

Make a new class (let's call it Circle) that says it's going to use the Shape blueprint (`class Circle : public Shape`).
Inside Circle, you will write the actual code for setPosition, setColor, and getDrawable functions. This code will specifically handle how a circle changes its position, color, and how it should be drawn.

### Task 3: Modify the Game Class to Use the Shape Abstraction

What to Do:

Change the Game class so it doesn't directly create and use a circle but instead talks to the Shape blueprint. This way, Game doesn't care what shape it's dealing with, making it easier to add new shapes later.

How to Do It:

In the Game class, instead of having a CircleShape object, have a Shape pointer. This pointer can point to any shape (like a circle, square, etc.) that follows the Shape blueprint.
Update the game's code so whenever it needs to move the shape, change its color, or draw it, it calls the Shape functions. Since Circle implements Shape, the game can use a Circle (or any other shape that follows the Shape blueprint) without knowing the details.

### Why Do This?

Flexibility: Later, if you want to add a new shape, like a square, you just need to create a Square class that follows the Shape blueprint. You don't need to change the Game class.
Maintainability: Your code is easier to update and maintain. Changes in how a shape behaves or is drawn only need to be made in one place.

[^1]: In programming, "wrapping" refers to the technique of encapsulating or embedding an object, function, or data within another object or class, often to provide a simplified, enhanced, or different interface to the underlying functionality. The wrapper class (RandomCircle, for example) implements a defined interface (Shape) and manages the underlying sf::Shape object. 
  This way, the specific details of how shapes are managed and drawn are abstracted away from the rest of the application, allowing the Game class to operate on a higher level of abstraction without concerning itself with the specifics of SFML's drawing mechanisms.
