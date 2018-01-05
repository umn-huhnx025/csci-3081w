# Design Justifications for FlashPhoto
#### Group Name:
Curlin

#### Members:
- Henry Mark
- Kent Miller
- Jon Huhn

#### Instructions
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.  
> A few tips to maximize the success of your design document:  
>   1. Make sure the **description** of your design decision only contains an objective description of how you structured your design and how it was implemented (specifically how your solution solves the problem given in the prompt). Save any arguments in favor of your design for the **justification** section.
>
>   2. Your justification will probably need to compare against at least one alternative, and you will need to provide a compelling argument for why your solution is better than the alternative.
>
>   3. Edit this file when writing your design document. Do not move or rename this file. Do not direct to any outside resources for your images or code. Place all images and code in this document. Please match the formatting of the [Example Design Document](https://github.umn.edu/umn-csci-3081F16/Example-Design-Document/blob/master/doc/DesignDocument.md) and [its source](https://raw.github.umn.edu/umn-csci-3081F16/Example-Design-Document/master/doc/DesignDocument.md?token=AAADyd5L8wd57F_qLX4Nf-2nVvfRlMj5ks5YH-qHwA%3D%3D) as precisely as possible, especially in regards to:
>     - **Formatting code** (do not include images of your code, make sure that your code is formatted with C++ coloring)
>     - **Inserting images**
>     - **Numbered lists for your tutorial**
>     - **Captioning your Figures**
>     - **Including the original prompts in their original quote form**  
>
>  This formatting helps us grade your assignments effectively, and thus failure to meet these requirements may result in point deductions. Any material that is not presented in this design document will not be graded.
>   4. When including a class diagram, only show the classes and members that convey the point you're trying to make. For example, showing the class BaseGfxApp in a UML diagram will probably not be appropriate.





## 1  Design Question One
> This iteration of the project introduces the concept of filters. You had to implement several filters, which fell into two types: pixel-independent (where each pixel is filtered independently), and convolution-based (where filtering a pixel requires information about its neighboring pixels by means of a kernel). Naturally, a key design decision is how these filters are represented. Each filter has a different algorithm for modifying the canvas, and only some of these algorithms require kernels.
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description

Our central thought in implementing filters for this iteration was to approach it in a way that guaranteed the highly technical nature of this requirement was abstracted away from the rest of the program's workings. Appropriately, the base code was presented to us in a way that encouraged this approach - a `filter_manager` class could encapsulate the inner workings of this functionality both robustly and elegantly. It also allowed us to ensure working implementation of the algorithms contained within would remain high on the list of priorities necessary in proper execution of the FlashPhoto application.

We started out by developing for the pixel-independent filters as these proved trivial in difficulty when placed against filters in which pixel value's house a dependency on neighboring pixel values. The base code provided offered sufficient data members in order to develop functional algorithms; the only critical component lacking was a reference to the canvas, which we passed to the `filter_manager` constructor for initialization.

####Figure 1: FilterManager Relationship
![Figure 1](https://github.umn.edu/umn-csci-3081F16a/repo-group-Curlin/blob/master/doc/figures/FilterManagerUML.png)

Demonstrated here, the `FilterManager` comprises several algorithms required in order to alter the canvas as required for each particular filter. The ability to invoke these functions is driven by `FlashPhotoApp` and reflected in `FlashPhotoApp`'s `PixelBuffer` instance.

These pixel-independent filters and the algorithms necessary to their implementation is entirely self-contained within their respective member functions of `filter_manager`. The same can be said of convolution-based filters, with a small nuance that separates itself from the rest, which shall be mentioned shortly. With this, the `ApplyThreshold`, `ApplySaturate`, `ApplyChannel`, and `ApplyQuantize` filters were established and functional.

Convolution-filters added a second layer of complexity to the filter development. These would require overlaying a kernel array with the existing `PixelBuffer` array in order to determine updated values appropriate for the given filter effect. In general, the back-half of this process (applying the kernel to the canvas) is the same for all convolution filters, regardless of the desired effect of a particular filter. For this reason, an `ConvoluteCanvas` member function was added to the `filter_manager`. The importance of this function is realized through the call designated from any of the required convolution filters: `ApplyBlur`, `ApplyMotionBlur`, `ApplyEdgeDetect` and `ApplySharpen` all depend on this function call in order to handle application of the kernel to the canvas. This relieves the aforementioned member functions to the duty of generating a kernel and destroying the kernel in memory upon completion of the application.

In our implementation, each of the filters exists as something of a "module" function within the `filter_manager` class which encapsulates all of the filtering functionality for FlashPhoto. Next we will discuss the reason we determined this approach to be appropriate for our desired design of the finalized applicaiton.

### 1.2 Design Justification

When we began constructing the components necessary for this iteration, it was evident that we would need to write efficiently and quickly in order to complete the iteration by the declared deadline. We gave careful consideration to two possible implementations of the filtering algorithms. The first option would be to encapsulate the filters within an all-encompassing class or delegate them to their own, independent classes.

In considering the latter option, there was cetainly some allure in pursuing this design. First, it would greatly enhance the modularity of the larger program design. The `filter_manager` could exist as a controller for calling upon appropriate classes in order to fulfill the selected filter, and the algorithmic processes could be abstracted away. Should any particular algorithm break, the core functionality of the `filter_manager` would be preserved. This also offers something in the way of extensibility: should the core criteria of image filtering change, a new class could be added in order to handle the new requirements.

Ultimately, we voted against this option for a few reasons. While the modularity would be nice, it didn't make sense to have an entire class just to implement one filter. This would greatly expand an already large file count and convolute the program structure. With a few exceptions, the filters are distinctly different enough that it wouldn't make sense to virtualize a `Filter` class and implement a `Strategy` pattern module either.

In ruling out this approach, we made the decision to unite the filters within the `filter_manager` class. This was an important decision as it allowed us to hit the ground running on this iteration and begin coding the filters immediately: most of the base code for the `filter_manager` was provided in a way that encouraged this approach, further confirming to us that this was the correct approach. This also prevented us any lost time in setting up new classes for functionality that doesn't require it.

In the process of writing these filtering algorithms, we sought to exploit any pattern that would allow us extensibility in our codebase; though we weren't creating new classes here, we could still utilize the same tactics through wise decision-making in our function layout. For example, it was important to note that several convolution filters exhibit similar behavior: `ApplyEdgeDetect` and `ApplySharpen` have a nearly identical kernel, with a center-value incremented by 1. For this reason, a previously unincluded `ConvoluteCanvas` function was added. Now, we could pass it any rational kernel and it would handle application of that kernel to the canvas. This inclusion greatly simplified our convolusion-based filter functions, and increased the reuse of our existing code.

The one drawback to the approach we took is the larger filesize associated with encapsulating the filters in a single entity. The `filter_manager` class by line count is larger than we anticipated, though in considering the alternative, we agree that we prefer the larger filesize to the fragmentation of our filtering algorithms offered in the other option.

In all, we think we've made a wise design decision for implementing the image filters for several reasons. The encapsulation of this program functionality offers a much more simplistic, organized solution, it allowed us a greater allotment of time to ensure that the algorithms worked first and foremost, and it provided several aspects we favored of the opposing option while avoiding a few of its shortcomings.

## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

In implementing the Undo and Redo functionality in our FlashPhoto iteration, we chose to design for the highest degree of encapsulation we could, using an Observer pattern.  In doing so we have designed and contained a specialized class for our stack of `PixelBuffer`s that ultimately represent any undo/redo operation.  No other design patterns were necessary to accomplish this task, Strategy and Factory aren't applicable, and Template is not quite amenable to our approach (which will be discussed in more detail below).  Some of the decision was made for us, as the `StateManager` class was included in the base code, and our further developments only interated on top of this base.

#### Figure 2: UML Diagram
![Figure 2](https://github.umn.edu/umn-csci-3081F16a/repo-group-Curlin/blob/master/doc/figures/StateManagerUML.png)

As can be seen in the diagram above, the `FlashPhotoApp` has a reference to the `StateManager`, which is what was provided in the base code.  This is the primary driving factor for why we implemented an Observer pattern in our program, the `StateManager` was already set up as a listener, or Observer, of the `App` for us.  All we did was allow the manager to be notified of changes by the `App` and to update its stacks accordingly.  Also note here that the stacks hold references to pointers to `PixelBuffer`s, not just references to `PixelBuffer`s.  This allows minimal disturbance of the `App` when an undo or redo changes the canvas, since they only enact a passive change to the canvas's current address.

Using a stack is the obvious choice here; we need a data structure that is last-in, first-out for both undo-ing and redo-ing.  Having the stacks be aware of the `App` and the specific canvas being drawn, but not vice versa, is also a necessary and obvious choice.  The undo and redo operation should change the image rendered to the screen, but the `App` and the current canvas need not be aware of the changes (they carry on operation as if nothing had indeed changed).  Following in this direction, we ended up at our decision to have our specialized stacks be part of the `StateManager`, which controls everything that goes into and out of the stacks by interacting with the `App`.

The way in which we designed these stacks permits us to not change anything about the canvas being currently rendered to the screen.  Instead, any time a change is about to take place (a filter operation is begun, the user draws on the canvas, etc.) the undo stack is sent a copy of the current canvas.  If a change is to be undone, the stack takes the most recent copy of the canvas and changes the `App`s pointer to the canvas towards that copy, effectively undo-ing the change.  At the same time, the redo stack is made aware of this undo operation and adds the new/undone canvas to its stack, so that the operation can be redone.

The effect on the overall code base in carrying out this design was negligible.  Indeed, this design is highly extensible, only requiring a single line of code to be added to be able to undo/redo any canvas-changing operation that may be later added to the `FlashPhotoApp`.  This is a direct result of Observer; anything the user would like to undo/redo needs only the notify the `StateManager` of this fact, and the changes made will automatically be stored in the undo/redo buffer.  One could even, in the future, allow the `App` to dynamically allow undo/redo operations depending on the program state, though that is outside the scope of this document.

It should be pointed out that a Template design is technically possible for implementing an undo/redo stack.  We will discuss this in our justification for the design outlined above.

### 2.2 Design Justification

We will begin our justification by addressing an alternate design.  As we said, Template is probably the most obvious design decision that we could have implemented.  It would have allowed our stacks to be more robust should any non-canvas undo/redo functionality be desired.  There are a few reason why we chose to create our own custom stacks.

First, as can be seen in Figure 1 above, we have a special `Trash()` method which is not found in the C++ stack template.  This method iterates through the whole of the stack, sets all the pointers to null, and resets the index of the stack, and this is necessary for us here because we aren't storing `PixelBuffer`s, but rather _pointers_ to `PixelBuffer`s, which must be handled carefully so as to keep from forming a memory leak.  The method is used to clear the redo stack when a new user action is taken (since you can't redo if the most recent action is a user modification of the canvas).

Second, there is no need to implement extensibility to undo/redo.  What could the user possibly hope to undo/redo in their drawing/photomanipulation app that has nothing to do with the canvas?  We could think of nothing, and so we decided that figuring out how to make a template work in this situation was more hassle than necessary.

However, the big advantage a template would have is that it is already made, ready to go out-of-the-box.  Such a pattern would have allowed us to add undo/redo functionality with only a few lines of code, instead of our own custom class.  It also would not have broken our Observer pattern, since such a Template would work by using built-in stacks that could be updated from the `StackManager`. This advantage would have been considerably weakened by our requirement to completely empty out the redo stack upon a new user-action being logged.  It is ultimately for this reason that we decided to create our own custom stack class.

The alternative to Observer pattern would be for the `FlashPhotoApp` to be aware of undo/redo functionality.  We described why the `App` being unaware is superior in the design description above, but we discuss it here to illustrate just why it is superior.

Consider an `App` that knows all about undo and redo.  Such an `App` must therefore keep track directly of stacks that store all the changes to the canvas over the operation of the program.  Instead of notifying another class that a change had occurred, the `App` would need to copy its canvas and store it in a stack that was defined inside of the `App` body proper.  Then it would need functionality for recovering and displaying an old copy of the canvas.  There's nothing technically wrong with this approach (it would compile and run just fine, and may even have saved a few pointer-related headaches), except that it violates what the `FlashPhotoApp` _is_.  The `App` is the program that controls the canvas and the operations carried out on it, and adding undo and redo to the `App` itself would be extending it from a canvas controller to a meta-controller that controls itself and its previous selves.  This modification weakens the definition of the `App`, and it also would make it harder to find dangerous bugs in the code by adding dozens of lines of code to the body of the `App`.

Thus it is our opinion that the Observer method with a custom stack class framework is the best practice that we could carry out to implement undo/redo functionality.  It is highly extensible, robust, and encapsulated, and, most importantly, it works very well with minimal changes to the `App` code body proper.

## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

### Programming Tutorial: Adding a New Invert Filter to FlashPhoto

1. First, add a `UI_APPLY_INVERT` element to the `Type` enum in the `UICtrl` class as shown below:  
 ###### src/include/ui_ctrl.h  
 ``` C++
 enum Type {
    UI_TOOLTYPE,
    UI_COLOR_R,
    UI_COLOR_G,
    UI_COLOR_B,
    ...
    UI_APPLY_INVERT,
    ...
}
 ```

2. Next, create the user interface for the filter. In the `FilterManager::InitGlui()` method, add a `GLUI_Panel *invert_panel` to the rest of the filters with the label "Invert" and an "Apply" button.  
 ###### src/filter_manager.cc  
 ```C++
void FilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
      ...
      GLUI_Panel *invert_panel = new GLUI_Panel(filter_panel, "Invert");
  
      {
        new GLUI_Button(invert_panel, "Apply", UICtrl::UI_APPLY_INVERT,
                        s_gluicallback);
      }
    }
 ```

3. Next, create the logic for the filter. In the `FilterManager` class declaration, declare a `ApplyInvert` method that takes no arguments and returns void.  
 ###### src/include/filter_manager.h  
 ```C++
class FilterManager {
      ...
      void ApplyInvert(void);
      ...
}
 ```  

4. Finally, in the `FilterManager` implementation file, define the `ApplyInvert` method declared in the previous step. This method works by iterating through each pixel in the canvas, creating a new `ColorData` object with the inverted red, green, and blue values, and setting the old pixel in the canvas to the newly created `ColorData`. Note: in this implementation, the alpha value is not changed.  
 ###### srcc/filter_manager.cc  
 ```C++
/*******************************************************************************
 * Member Functions
 ******************************************************************************/

 ...

void FilterManager::ApplyInvert(void) {
      // Iterate through each pixel in the canvas
      for (int canvas_y = 0; canvas_y < (*display_buffer_)->height(); canvas_y++) {
        for (int canvas_x = 0; canvas_x < (*display_buffer_)->width(); canvas_x++) {
    
          // Copy the current color on the canvas
          ColorData canvas_pixel =
              (*display_buffer_)->get_pixel(canvas_x, canvas_y);
    
          // Calculate inverted colors
          float new_red = 1.0 - canvas_pixel.red();
          float new_green = 1.0 - canvas_pixel.green();
          float new_blue = 1.0 - canvas_pixel.blue();
          float new_alpha = canvas_pixel.alpha();
    
          // Make a new ColorData object with the new values
          ColorData new_color = ColorData(new_red, new_green, new_blue, new_alpha);
    
          // Set the canvas pixel color to the new color
          (*display_buffer_)->set_pixel(canvas_x, canvas_y, new_color);
        }
      }
    
      std::cout << "Apply has been clicked for Invert" << std::endl;
}
...
 ```
