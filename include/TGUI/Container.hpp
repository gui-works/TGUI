/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2013 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_CONTAINER_HPP
#define TGUI_CONTAINER_HPP


#include <list>

#include <TGUI/Widget.hpp>
#include <TGUI/EventManager.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    struct Callback;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Parent class for widgets that store multiple widgets.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Container : public Widget
    {
      public:

        typedef SharedWidgetPtr<Container> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container(const Container& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container& operator= (const Container& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the global font.
        ///
        /// This font will be used by all widgets that are created after calling this function.
        ///
        /// \param filename  Path of the font file to load
        ///
        /// \return True if loading succeeded, false if it failed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setGlobalFont(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the global font.
        ///
        /// This font will be used by all widgets that are created after calling this function.
        ///
        /// \param font  Font to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setGlobalFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the global font.
        ///
        /// This is the font that is used for newly created widget by default.
        ///
        /// \return global font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getGlobalFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of all the widgets.
        ///
        /// \return Vector of all widget pointers
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector< Widget::Ptr >& getWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of the names of all the widgets.
        ///
        /// \return Vector of all widget names
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<sf::String>& getWidgetNames();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds an widget to the container.
        ///
        /// \param widgetPtr   Pointer to the widget you would like to add
        /// \param widgetName  If you want to access the widget later then you must do this with this name
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container); // Create a picture and add it to the container
        /// container.remove(pic);             // Remove the picture from the container
        /// container.add(pic);                // Add the picture to the container again
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void add(const Widget::Ptr& widgetPtr, const sf::String& widgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to an earlier created widget.
        ///
        /// \param widgetName The name that was given to the widget when it was added to the container.
        ///
        /// \return Pointer to the earlier created widget
        ///
        /// \warning This function will return nullptr when an unknown widget name was passed.
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2 = container.get("picName");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr get(const sf::String& widgetName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Makes a copy of any existing widget and returns the pointer to the new widget.
        ///
        /// \param oldWidget     A pointer to the old widget.
        /// \param newWidgetName If you want to access the widget later then you must do this with this name
        ///
        /// \return Pointer to the new widget
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2 = container.copy(pic, "picName_2");
        /// tgui::Picture::Ptr pic3 = container.copy(container.get("picName"), "picName_3");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr copy(const Widget::Ptr& oldWidget, const sf::String& newWidgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single widget that was added to the container.
        ///
        /// \param widget  Pointer to the widget to remove
        ///
        /// \see remove(sf::String)
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(container, "picName");
        /// tgui::Picture::Ptr pic2(container, "picName2");
        /// container.remove(pic);
        /// container.remove(container.get("picName2"));
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single widget that was added to the container.
        ///
        /// \param widget  Pointer to the widget to remove
        ///
        /// This function is provided for internal use.
        /// The other remove function will probably be easier to use, but in the end they do exactly the same.
        ///
        /// \see remove(Widget::Ptr)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(Widget* widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all widgets that were added to the container.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses an widget.
        ///
        /// The previously focused widget will be unfocused.
        ///
        /// \param widget  The widget that has to be focused.
        ///
        /// \see unfocusWidget
        /// \see unfocusAllWidgets
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusWidget(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocus an widget.
        ///
        /// The next widget will be focused.
        ///
        /// \param widget  The widget that has to be unfocused.
        ///
        /// \see focusWidget
        /// \see unfocusAllWidgets
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusWidget(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocus all the widgets.
        ///
        /// \see focusWidget
        /// \see unfocusWidget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Uncheck all the radio buttons.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheckRadioButtons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places an widget before all other widgets.
        ///
        /// \param widget  The widget that should be moved to the front
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToFront(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places an widget behind all other widgets.
        ///
        /// \param widget  The widget that should be moved to the back
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToBack(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Bind a function to the callbacks of all child widgets.
        ///
        /// When a child widget tells this widget about the callback then the global callback function(s) will be called.
        /// If no global callback function has been bound then the callback is passed to the parent of this widget.
        ///
        /// \param func  Pointer to a free function with a reference to a Callback widget as parameter.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void bindGlobalCallback(std::function<void(const Callback&)> func);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Bind a function to the callbacks of all child widgets.
        ///
        /// When a child widget tells this widget about the callback then the global callback function(s) will be called.
        /// If no global callback function has been bound then the callback is passed to the parent of this widget.
        ///
        /// \param func      Pointer to a member function with a reference to a Callback widget as parameter.
        /// \param classPtr  Pointer to the widget of the class.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        void bindGlobalCallback(void (T::*func)(const Callback&), T* const classPtr)
        {
            m_GlobalCallbackFunctions.push_back(std::bind(func, classPtr, std::placeholders::_1));
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unbind the global callback function(s).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void unbindGlobalCallback();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads a form from a file.
        ///
        /// The widgets will be loaded and added to the container.
        /// Note that even when this function fails, some widgets might have been loaded already.
        ///
        /// \param filename  Filename of the widget file that is to be loaded
        ///
        /// \return
        ///        - true on success
        ///        - false when the file could not be opened
        ///        - false when the file contains a mistake
        ///        - false when one of the widgets couldn't be loaded
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool loadWidgetsFromFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is used internally by child widget to alert there parent about a callback.
        // If it reaches the gui, then the callback can be obtained by calling the pollCallback function of the gui.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void addChildCallback(const Callback& callback);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(sf::Keyboard::Key key);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 key);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is called every frame by EventManager.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Focuses the next widget in the container. If the last widget was focused then all widgets will be unfocused and
        // this function will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusNextWidgetInContainer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function will call the draw function from all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void drawWidgetContainer(sf::RenderTarget* target, const sf::RenderStates& states = sf::RenderStates::Default) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::vector<sf::String>  m_ObjName;

        sf::Font m_GlobalFont;

        // The internal event manager
        EventManager m_EventManager;

        // Is the container focused? If so, then one of the widgets inside the container may be focused
        bool m_ContainerFocused;

        // A list that stores all functions that receive callbacks triggered by child widgets
        std::list< std::function<void(const Callback&)> > m_GlobalCallbackFunctions;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        friend class EventManager;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API GuiContainer : public Container
    {
      public:

        typedef SharedWidgetPtr<Container> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unbind the global callback function(s).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unbindGlobalCallback();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Doesn't has any effect.
        ///
        /// \param width   Ignored
        /// \param height  Ignored
        ///
        /// The window size cannot be changed by a widget.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the container (same size as the window).
        ///
        /// \return Size of the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /// Returns a nullptr.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual GuiContainer* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /// Returns false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /// This function does nothing.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        sf::RenderWindow* m_Window;


        friend class Gui;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CONTAINER_HPP
