# Design Justifications for BrushWork
#### Group Name:
Curlin

#### Members:
- Henry Mark
- Kent Miller
- Jon Huhn

#### Instructions
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## 1  Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner.
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description
Our solution to implementing the `Tool` class was to use the Strategy pattern.  The conceptualization we used for `Tool`s is based on the real-world application of a drawing tool; a `Pen` (for example) 'is a' `Tool`, which 'has a' `Mask` (which is the specific style it draws with) and it 'has a' `DrawBehavior`.  The following diagram describes the general structure of our Strategy pattern for `Tool`s.

#####Figure 1: Outline of Tool Strategy Pattern

![Strategy Pattern UML Diagram](https://github.umn.edu/umn-csci-3081F16a/repo-group-Curlin/blob/master/doc/figures/StrategyPattern.png)

This diagram shows the generic `Tool` class, which 'has a' `DrawBehavior` and (for this iteration) a `Mask`.  The `Mask` should be thought of as physically part of the tool, it is the felt tip of a marker or the ball point of a pen -- it describes the unique footprint of the `Tool` on the canvas.  The `DrawBehavior` is _how_ the tool draws on the canvas, whether by a `Mask` or by some other method.  We will note here as well as in the Design Justification section that no current `Tool` draws any differently than any other `Tool`, but we include a `DrawBehavior` class because it allows for non-`Mask` bearing `Tools` to be implemented in the future.  There is also a `ToolController` class, which is the go-between for the `BrushWorkApp` (which uses int values for tools) and the specific `Tool` objects.  The `ToolController` contains a "tool box" to hold all of the various drawing utensils used by the App.  This is useful to abstract away the `Tool` creation and handling process, so that the App only needs to worry about making the controller and asking for whichever `Tool` it is currently using.

We show in the following UML diagram how these classes relate to one another, using a Pen class as an example:

#####Figure 2: UML Diagram with Class Relationships
![UML Diagram](https://github.umn.edu/umn-csci-3081F16a/repo-group-Curlin/blob/master/doc/figures/UML_Diagram.png)

Off to the left of the diagram is the `BrushWorkApp` class, which 'has a' `ToolController`.  In the diagram we see the `ToolController` has any amount of `Tool`s, which themselves have exactly 1 `DrawBehavior` and either 0 or 1 `Mask`s.  `Pen` (`Tool`s child) 'has a' `PenMask` and `DrawBehaviorMask`. In this iteration each unique tool has a `[Tool]Mask` class, which stores the "footprint" of that particular tool.  This is necessary because no two unique masks have exactly the same footprint (or even size in most cases).

When a specific `Tool` is called by the App to draw on the screen, the `ToolController` selects the appropriate `Tool` from its `tool_belt_`.  That `Tool` then calls `DrawAt()`, which invokes the `DrawBehavior` specific to that `Tool`, applying colors to the canvas according to the `DrawBehavior`.  Below are a few snippets/abbreviations of code from our project, showing the example `Pen` class -- how it is created and how it relates to its other classes in implementation.

#####Figure 3: `ToolController` and `Pen` Classes

###### `Pen`
```C++
void Pen::Initialize(const float* red, 
      const float* green,
      const float* blue,
      const ColorData* background_color) {
  /** Background color is not required for a Pen, but we set it in case it
      may ever need to use it in the future.*/
  background_color_ = background_color;  
  red_ = red;
  green_ = green;
  blue_ = blue;
  mask_ = new PenMask(3);     // Diameter 3
  DrawBehaviorMask* dbm = new DrawBehaviorMask(red_, green_, blue_, mask_);
  draw_behavior_ = dbm;       // The Pen's specific DrawBehavior
}

void Pen::DrawAt(int x, int y, PixelBuffer* canvas) {
  draw_behavior_->DrawAt(x, y, canvas);   // DrawBehavior takes care of the details
}
```

Here we see `Pen` getting Initialized.  It has a `PenMask` type `Mask` with `diameter` 3.  It has a `DrawBehaviorMask` type of `DrawBehavior`, which is set up with both the current colors (pointers to where the current colors are stored in the App) as well as the `PenMask`.  This allows `DrawBehavior` to implement the same `DrawAt()` function for every possible drawing behavior, as it keeps the implementation removed from the Abstract type.

###### `ToolController`
```C++
/* Sets up the tool_box_ with all the different Tools **/
void ToolController::Initialize(const float* red, const float* green,
                                const float* blue, const ColorData bc) {
  ptr_red_ = red;
  ptr_green_ = green;
  ptr_blue_ = blue;
  background_color_ = &bc;

  /** @TODO CONSTRUCT TOOLS USING COLORS PROVIDED ABOVE */
  int num_tools = 6;  // Pen, Callig. Pen, Highlighter, Spray, Eraser, Special
  tool_box_ = new Tool[num_tools];
  // Pen
  Pen* pen = new Pen(
        ptr_red_,
        ptr_green_,
        ptr_blue_,
        background_color_);
  tool_box_[0] = *pen;

  // Eraser
  Eraser* eraser = new Eraser(background_color_);
  tool_box_[1] = *eraser;

  // Spray Can
  SprayCan* spray_can = new SprayCan(
        ptr_red_,
        ptr_green_,
        ptr_blue_,
        background_color_);
  tool_box_[2] = *spray_can;

  // ... Other tools also defined
}

Tool* ToolController::GetCurrentTool(int cur_tool) {
  return &tool_box_[cur_tool];
}
```

Here we see the `ToolController` getting initialized.  A "`tool_box_`" `Tool` array is created and filled with `Tools` that get initialized with the current rgb and background colors (which are references to the address where the App keeps these data).  `GetCurrentTool` is the method by which `ToolController` acts as the go-between for the App and the `Tools`.

This is our overall design, applied to each of the children of `Tool`.  However, these decisions are as-yet unjustified.  In the following section we will explain why we chose a Strategy pattern, some alternatives, and why `ToolController` has the `Tool`s intializations hard-coded into the `tool_box_`, rather than making use of a Factory pattern.


### 1.2 Design Justification

[Hopefully] obviously, one does not wish to have enormous, unmaintainable classes.  Indeed this was our thinking when we chose our level of encapsulation for each abstract idea we wished to implement.  Our philosophy as we designed the overall structure for this iteration was one of realistic encapsulation; we sought to have classes that, as closely as could be managed, mirror the real-world counterparts of the tools being implemented.

####Thinking Strategically

Starting at the top (the App), instead of the `BrushWorkApp` class containing _n_ tools, `Pen`, `Eraser`, `Highlighter`, etc., we chose to have a controller be in charge of creating and delivering those tools to the App as needed.  This is the genesis of the `ToolController`.  Once there is a controller, though, it needs some `Tool`s to control, and this is where we hit our first large design decision.

We could have chosen to implement a single `Tool` class, which contained within it an enum and switch-and-case to decide which `Tool` was to be currently used.  Such a file would quickly grow very large, and there would be a fair amount of copy/pasting.  We imagine such a structure would be outlined as follows:

#####A Bad Design: Single Tool Class
```C++
class Tool {
  /* Constructor */
  Tool(/* args */) { /* init */ }

  void SetCurrentTool(int tool_ID) { current_tool = tool_ID; }

  void DrawWithTool(int tool_ID) {
    switch(tool_ID) {
      case 0: /* Pen drawing algorithm*/
        break;
      case 1: /* Eraser drawing algorithm*/
        break;
      case 2: /* Highlighter drawing algorithm*/
        break;
      // etc ...
    }
  }

};
```

Clearly this could get out of hand as both the initialization of each tool would require variables to store the mask, and the helper functions and subtle differences of each tool would require their own special cases to be hard-coded into the ever-growing Tool file.

Hence we chose to abstract away the tools into their own respective classes, and it seemed obvious enough that each `Tool` had enough in common that a hierarchy could be formed.  `Tool`s have different footprints, so each one should have a mask.  And here is where our Strategy pattern comes in.  We could have reasonably chosen to include a 2D array of floats, called `mask_`, in each `Tool`.  This is only one variable, and initialization is unique to each type of `Tool`.  There wouldn't be a mountain of code building up, such an addition to the class would add maybe 10-20 lines of code.  However, we anticipate the possibility that, in the future, mask size may change dynamically at runtime.  If this becomes the case then there would be a gradual build-up of methods and special cases in the `Tool` class as functionality was added to allow this dynamic resizing.  Thus we chose to implement the Strategy pattern for `Mask`s, where there is a base type of `Mask` and there are children `[Tool]Mask`, which know how to initialize themselves for that type of `Tool`.  In the future, then, we can add a `Resize(int new_size)` function inside of each `[Tool]Mask`, abstracting away the need for a tool to change itself if ever this requirement is added -- a `Tool` simply says to its unique `[Tool]Mask` "Please change your size", and that `[Tool]Mask` just does.

This decision has an immediate consequence also.  The `Tool` classes (Pen, Highlighter, etc.) are less cluttered with `Mask` details, and thus easier to read and alter without breaking.  Our next decision, however, is made purely out of anticipation for future requirements, and has little immediate benefit, if not a small amount of additional work.  This is the aforementioned decision to implement a `DrawBehavior` family in our Strategy pattern.

####Preparing for the Future

All `Tool`s in this iteration draw in exactly the same way; they apply the proportion of color to the canvas as set in their mask values.  However, imagine a `PaintCanTool` which covers all of the canvas (or some amorphous region) in the same color.  There is no mask, there is no pre-defined region (in the case of filling like-colored pixels as in MS Paint).  Such a `Tool` doesn't fit the paradigm of a `Mask` bearing `Tool`.  So we made the decision to have all `Tool`s have only two things in common: a `Tool` can `DrawAt()` some place on the canvas, and it knows the current colors.  `DrawAt()` is therefore the choice for another application of the Strategy pattern.  By creating an abstract class called `DrawBehavior` we allow for any such future behaviors to be implemented without affecting in any way previous implementations.  The `Mask` bearing `Tool`s use a `DrawBehaviorMask`, while a `PaintCanTool` may use a `DrawBehaviorFillRegion`.  In this way we have future-protected ourselves from changing tool requirements/additions.

####Not a Factory in Sight

Lastly, there is the matter of a lack of a Factory strategy in our `ToolController`.  This seems like an obvious place to add a factory.  We are, after all, creating an array of `Tool`s depending on the array index, this could be fairly easily abstracted away into a factory.  The reasons we chose not to do this are: 1) the `Tool` creation will never be more complex in the `ToolController`, since a `Tool` is defined to only take colors as arguments while the actual `Tool` constructors will handle getting the additional parts; and 2) we don't expect there to be more than a dozen tools required for this program, so the long-term space savings would be fairly inconsequential.

The overall justification for our decisions is therefore that a Strategy pattern allows for useful abstraction while simultaneously allowing us to add additional features without breaking existing ones (i.e. future proofing).  By creating a more general `Tool` which doesn't necessarily require a `Mask`, we prepare for more versatile tools in the future, while compartmentalizing our existing `Mask` bearing `Tool`s.  And we believe our remaining non-Strategy code (`ToolController`) is reasonably extensible, not requiring a factory to generate more tools, as such a step is just as much work with the factory as without.


## 2  Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined.
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
Like all of the tools designated for this iteration, the `Eraser` inherits from the `Tool` class. That is, the `Eraser` 'is a' `Tool`. However, unlike the rest of the tools, the `Eraser` does not get passed floating point values associated with the red, green, and blue channels useful for applying a color to the canvas. Instead it receives only a reference to the canvas color. Being able to approach the problem in this way reaffirmed our decision to implement a strategy pattern.

A strategy pattern meant we were able to plan for `Tool`s that may not all behave in the same way. It allowed us to approach the `Eraser` design in a way that emphasizes concision; a perfect implementation would not be signified by robustness, but rather by precision and modularity.

Proceeding in this direction, we wanted to keep `Eraser` bound similarly to the makeup of the other tools. Instead of pursuing an approach that removes color from the canvas, it would be more consistent if the `Eraser` could draw to the canvas like other tools. This required us to instantiate an `EraserMask`, that serves the same purpose as the other `Mask`s. In order to do this, it was necessary for the `Eraser` to keep a reference to the canvas color. Combined with its drawing footprint, the `EraserMask`, the `Eraser` would be able to draw to the canvas.

In incorporating this approach, it became evident that if the `Eraser` should contain information regarding the canvas color, then perhaps the other tools should too. This was a design decision that had great influence over the remainder of the project, and solved several other issues, which shall be discussed in the following Design Justification section.

The decision to allow the `Eraser` to draw to the canvas allowed us to abstract the process of drawing to the canvas away from the `Tool`s. Abstractly, all `Mask`-bearing `Tool`s  utilize the same mechanism for applying themselves to the canvas. The variation in `Eraser`'s makeup could be accommodated for by calling the appropriate `DrawBehaviorMask` constructor.

As the `DrawBehaviorMask` serves as the abstraction for applying `Tool`s to the canvas, it contains enough versatility to adapt depending on the nature of the tool. `Eraser` was integral in our decision to handle drawing in this way; without a `Tool` such as `Eraser` that behaves in a unique way, we likely would have implemented drawing from within the `Tool` class, something we agreed would have been a poorer design decision moving into iteration two.

Nearing the end of the iteration, we encountered a bug that affected a crucial stepping stone in our `Eraser` design process: the `background_color` `ColorData*` object was being unexpectedly overwritten. Suddenly, we no longer had a correct reference to the canvas color, and our `Eraser` implementation no longer worked: the `Eraser` drew in black ink similar to a `Pen`. In order to save time in the debugging phase, we ultimately decided to create a small `PixelBuffer` function that would return a pointer to the background color. Now passing in this value, we were able to circumvent the bad behavior of our previous reference, and our `Eraser` would function as intended.

Given more time, we would have been capable of finding and resolving the bug. Our decision to implement a strategy pattern gave us enough flexibility in our design approach that we were able to fix the issue without breaking any working modulesd. For this reason, had we been tasked with designing this project again, we would approach it in the same way, despite the bug, due to it's robustness, encapsulation of key processes, and future-proof characteristics.

### 2.2 Design Justification
In order to cut down on unnecessary value passing and redundancy, it was necessary to design `Eraser` in a way that differentiates itself from the rest of the tools. The most obvious way was to strip the color channel `floats` and design the process of applying the `Eraser` to the canvas in a way that relies only on the existing canvas color. This simplified things greatly, as we already had an in-depth understanding of how to implement `Mask`-bearing `Tool`s. `Eraser` would behave in much the same way, with the small detail of its color application differing. This way we could avoid the path that involved developing a separate `Eraser` family of `Tool`s that functioned by actually removing from the canvas, instead of applying themselves to the canvas.

Strategy pattern offered us a great deal of potential for handling unexpected behavior. While `Eraser` is certainly one of these cases, we were repeatedly posing questions about the future implementation of our design. What if future tools don't have masks? What if they don't "draw" to the canvas, but actually remove from the canvas (i.e. a snipping tool)? What if they're not tools at all? These were all questions we asked ourselves, and we believe we found our answer in strategy pattern: by encapsulating components within "interchangeable algorithms" that could be overwritten, we could handle just about any situation moving forward.

For the existing `Tool`s in our `tool_box`, we were able to encompass all of their drawing ability within the `DrawBehaviorMask` class. That is, all `Mask`-bearing `Tool`s would apply themselves to the canvas in this manner. By creating the larger-scale `DrawBehavior` class, we can create any child-class in the future for handling changing of the canvas color, cutting and pasting, creating shapes, etc. This was a critical component that drew us towards designing with strategy pattern in mind.

`DrawBehaviorMask` is designed to be robust enough to handle a `Tool` such as `Eraser` which doesn't carry the same attributes that the `Pen`, `Highlighter`, or `Crayon` `Tool`s do. We can simply form a new constructor that can accept the attributes that the `Eraser` does have, `background_color` and a `mask`. Doing this allowed us to encapsulate the entirety of the drawing functionality and pull it out of the `Tool` classes. We think that this was an important design decision; leaving it where it was would lead to convolution, and perhaps force us to break code moving into iteration two.

In designing the `Eraser` `Tool`, we saw great potential for other classes to store a reference to the canvas as well. The usefulness for this again comes in the form of future-proofing. If in a potential future iteration the background color is say, pink, blending of the `tool_color` and the `background_color` will be necessary. By passing this `ColorData* object towards the `Tool` sub-classes, color-blending should be relatively straightforward.

Our decision-making through the debugging phase ultimately was a product of time allocation. In certain cases it may ultimately save time to re-do critical components than it would be to fix what may be simply broken. Fortunately, the compartmentalization of our code required us to do neither. Our application-critical components were left entact and we exhausted little time debugging the invalid pointer.

In all, we used strategy pattern approach to implement the `Eraser` tool. We wanted it to function mostly like the other `Tool` classes while trimming the components that would never be utilized. Doing it this way allowed us to fully abstract drawing functionality away from the `Tool` classes, and gained us the ability to accomodate for unexpected behavior heading into iteration two.

## 3  Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

1. First, create the PencilMask class to implement the new tool's mask. This class is part of the `image_tools` namespace and inherits from the `Mask` class. The mask should be one completely opaque pixel, but we'll implement nested `for` loops in case we want to change the size of the mask later.
    ###### src/include/pencil_mask.h
    ```C++
    class PencilMask : public Mask {
     public:
      // Default Constructor
      PencilMask(void);

      // Parameterized Constructor
      explicit PencilMask(int diameter);

      // Destructor
      virtual ~PencilMask(void);

     protected:
      void Initialize(int diameter);
    };
    ```

    ###### src/pencil_mask.cc
    ``` C++
    PencilMask::PencilMask(void) {}

    PencilMask::PencilMask(int diameter) { Initialize(diameter); }

    PencilMask::~PencilMask(void) {
      int rows = sizeof mask_ / sizeof mask_[0];
      for (int counter = 0; counter < rows; counter++) {
        delete[] mask_[counter];
      }
      delete[] mask_;
    }


    void PencilMask::Initialize(int diameter) {
      diameter_ = diameter;

      // Initialize mask_ as new 2D square array of floats
      // Set each mask element to 1.0
      mask_ = new float*[diameter];
      for (int row = 0; row < diameter; row++) {
        mask_[row] = new float[diameter];
        for (int col = 0; col < diameter; col++) {
            mask_[row][col] = 1.0;
        }
      }
    }
    ```

2. Next, create the Pencil class. This class is part of the `image_tools` namespace and inherits from the `Tool` class. Don't forget to `#include` the header file for the PencilMask class. The parameterized constructor calls `Initialize`, which does all the real work. It sets all of the members for the `Pencil` object, including colors, a `PencilMask` of diameter 1, and a `DrawBehavior` to control how this tool will draw to the canvas.
    ###### src/include/pencil.h
    ``` C++
    ...
    #include "include/pencil_mask.h"
    ...

    class Pencil : public Tool {
     public:
      // Default Constructor
      Pencil(void);

      // Parameterized Constructor
      Pencil(const float* red, const float* green, const float* blue,
             const ColorData* background_color);

      // Destructor
      virtual ~Pencil(void);

     private:
      PencilMask* mask_;
      void Initialize(const float* red, const float* green, const float* blue,
                      const ColorData* background_color);
    };
    ```

    ###### src/pencil.cc
    ``` C++
    Pencil::Pencil(void) {}

    Pencil::Pencil(const float* red, const float* green, const float* blue,
             const ColorData* background_color) {
      Initialize(red, green, blue, background_color);
    }

    Pencil::~Pencil(void) {
      delete background_color_;
      delete red_;
      delete green_;
      delete blue_;
    }



    void Pencil::Initialize(const float* red, const float* green, const float* blue,
                         const ColorData* background_color) {
      background_color_ = background_color;
      red_ = red;
      green_ = green;
      blue_ = blue;
      mask_ = new PencilMask(1);
      draw_behavior_ = new DrawBehaviorMask(red_, green_, blue_, mask_);
    }
    ```

3. Next, add the tool to the `ToolController`'s '`tool_box_` to make it available within `BrushWorkApp`. Don't forget to `#include` the header file for the `Pencil` class and increment the local `num_tools` variable which controls the size of the `tool_box_` array.
    ###### src/tool_controller.cc
    ``` C++
    ...
    #include "include/pencil.h"
    ...

    void ToolController::Initialize(const float* red, const float* green,
                                    const float* blue, const ColorData bc) {
    ...
    int num_tools = 7;
    ...
    Pencil* pencil = new Pencil(ptr_red_, ptr_green_, ptr_blue_, background_color_);
    tool_box[6] = *pencil;
    }
    ```

4. Finally, add a radio button to the GUI with the label "Pencil" in the `BrushWorkApp::InitGlui` method.
    ###### src/brushwork_app.cc
    ``` C++
    void BrushWorkApp::InitGlui(void) {
      ...
      // Create interface buttons for different tools:
      new GLUI_RadioButton(radio, "Pen");
      new GLUI_RadioButton(radio, "Eraser");
      new GLUI_RadioButton(radio, "Spray Can");
      new GLUI_RadioButton(radio, "Caligraphy Pen");
      new GLUI_RadioButton(radio, "Highlighter");
      new GLUI_RadioButton(radio, "Crayon");
      new GLUI_RadioButton(radio, "Pencil");
      ...
    }
    ```
