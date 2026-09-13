# Homework #4 : Physical Simulator
## Objectives 
- Modify the app Physical Simulator according to homework tasks (please, see the file `04.homework_345726_e2be11-345726-51a13b.pdf`).

## Homework Implementation
### 1. Main Task
**Task** : Modify classes World and Ball to make possible to start the app and show moving balls on the screen.

**Implementation**
1. Next fields are added to the class Ball as their data is used by other classes in the app:
    - _Point_ center_;
    - _Velocity_ velocity_;
    - _double_ radius_;
    - _bool_ isCollidable_;
    - _Color_ color_.
1. Implemented the member functions of the class `Ball`.
1. The constructor of the class `World` was modified to read the information about balls from the file, create ball objects and put them to the vector of the class `World`.

The resulting git branch is [otus/HW-04-physics-main-problem](https://github.com/elbuscadordea/cpp-basics-hw-otus/tree/otus/HW-04-physics-main-problem).
