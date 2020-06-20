/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2020 Bruno Van de Velde (vdv_b@tgui.eu)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Container widget
    ///
    /// Parent class for widgets that contain child widgets.
    ///
    /// Signals:
    ///     - Inherited signals from Widget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Container : public Widget
    {
    public:

        typedef std::shared_ptr<Container> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Container> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container(const Container& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Move constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container(Container&& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Container();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of copy assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container& operator= (const Container& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of move assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Container& operator= (Container&& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the container
        /// @param size  The new size of the container
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of all the widgets in this container
        ///
        /// @return Vector of all widget pointers
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::vector<Widget::Ptr>& getWidgets() const
        {
            return m_widgets;
        }

#ifndef TGUI_REMOVE_DEPRECATED_CODE
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of the names of all the widgets in this container
        ///
        /// @return Vector of all widget names
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_DEPRECATED("Use getWidgets() and Widget::getWidgetName instead") const std::vector<sf::String> getWidgetNames() const
        {
            std::vector<sf::String> m_widgetNames;
            m_widgetNames.reserve(m_widgets.size());
            for (std::size_t i = 0; i < m_widgets.size(); ++i)
                m_widgetNames.emplace_back(m_widgets[i]->getWidgetName());

            return m_widgetNames;
        }
#endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a widget to the container
        ///
        /// @param widgetPtr   Pointer to the widget you would like to add
        /// @param widgetName  You can give the widget a unique name to retrieve it from the container later
        ///
        /// @warning The widget name should not contain whitespace
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void add(const Widget::Ptr& widgetPtr, const sf::String& widgetName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to a widget that was added earlier
        ///
        /// @param widgetName The name that was given to the widget when it was added to the container
        ///
        /// The container will first search for widgets that are direct children of it, but when none of the child widgets match
        /// the given name, a recursive search will be performed.
        ///
        /// @return Pointer to the earlier added widget
        ///
        /// @warning This function will return nullptr when an unknown widget name was passed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr get(const sf::String& widgetName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to a widget that was added earlier
        ///
        /// @param widgetName The name that was given to the widget when it was added to the container
        ///
        /// @return Pointer to the earlier added widget.
        ///         The pointer will already be casted to the desired type
        ///
        /// The container will first search for widgets that are direct children of it, but when none of the child widgets match
        /// the given name, a recursive search will be performed.
        ///
        /// @warning This function will return nullptr when an unknown widget name was passed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <class T>
        typename T::Ptr get(const sf::String& widgetName) const
        {
            return std::dynamic_pointer_cast<T>(get(widgetName));
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a single widget that was added to the container
        ///
        /// @param widget  Pointer to the widget to remove
        ///
        /// @return True when widget is removed, false when widget was not found
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool remove(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all widgets that were added to the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllWidgets();

#ifndef TGUI_REMOVE_DEPRECATED_CODE
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the name of a widget
        ///
        /// @param widget  Widget of which the name should be changed
        /// @param name    New name for the widget
        ///
        /// @return True when the name was changed, false when the widget wasn't part of this container.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_DEPRECATED("Use Widget::setWidgetName instead") bool setWidgetName(const Widget::Ptr& widget, const std::string& name);
        using Widget::setWidgetName;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the name of a widget
        ///
        /// @param widget  Widget of which the name should be retrieved
        ///
        /// @return Name of the widget or an empty string when the widget wasn't part of this container or wasn't given a name
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_DEPRECATED("Use Widget::getWidgetName instead") std::string getWidgetName(const Widget::ConstPtr& widget) const;
#endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Unchecks all the radio buttons
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheckRadioButtons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the space available for widgets inside the container
        /// @return Size of the container
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the distance between the position of the container and a widget that would be drawn inside
        ///        this container on relative position (0,0)
        ///
        /// @return Offset of the widgets in the container
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getChildWidgetsOffset() const
        {
            return Vector2f{0, 0};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of all existing and future child widgets
        ///
        /// @param size  The new text size
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a text file
        ///
        /// @param filename  Filename of the widget file
        /// @param replaceExisting  Remove existing widgets first if there are any
        ///
        /// @throw Exception when file could not be opened or parsing failed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromFile(const std::string& filename, bool replaceExisting = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the child widgets to a text file
        /// @param filename  Filename of the widget file
        /// @throw Exception when file could not be opened for writing
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void saveWidgetsToFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a string stream
        ///
        /// @param stream  stringstream that contains the widget file
        /// @param replaceExisting  Remove existing widgets first if there are any
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromStream(std::stringstream& stream, bool replaceExisting = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the child widgets from a string stream
        ///
        /// @param stream  stringstream that contains the widget file
        /// @param replaceExisting  Remove existing widgets first if there are any
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void loadWidgetsFromStream(std::stringstream&& stream, bool replaceExisting = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the child widgets to a text file
        ///
        /// @param stream  stringstream to which the widget file will be added
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void saveWidgetsToStream(std::stringstream& stream) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget before all other widgets
        ///
        /// @param widget  The widget that should be moved to the front
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToFront(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a widget behind all other widgets
        ///
        /// @param widget  The widget that should be moved to the back
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveWidgetToBack(const Widget::Ptr& widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the child widget that is focused inside this container
        ///
        /// @return Focused child widget or nullptr if none of the widgets are currently focused
        ///
        /// If the focused widget is a container then a pointer to that container is returned. If you want to know which widget
        /// is focused inside that container (recursively) then you should use the getFocusedLeaf() function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getFocusedChild() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the leaf child widget that is focused inside this container
        ///
        /// @return Focused leaf child widget or nullptr if none of the widgets are currently focused
        ///
        /// If the focused widget is a container then the getFocusedLeaf() is recursively called on that container. If you want
        /// to limit the search to only direct children of this container then you should use the getFocusedChild() function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr getFocusedLeaf() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses the next widget in this container
        /// @return Whether a new widget was focused
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusNextWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focuses the previous widget in this container
        /// @return Whether a new widget was focused
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusPreviousWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focus or unfocus the widget
        /// @param focused  Is the widget focused?
        ///
        /// When a widget is focused, the previously focused widget will be unfocused.
        ///
        /// @warning This function only works properly when the widget was already added to its parent (e.g. the Gui).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFocused(bool focused) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// Called when one of the child widgets of this container gains focus.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void childWidgetFocused(const Widget::Ptr& child);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rightMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rightMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void textEntered(std::uint32_t key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseWheelScrolled(float delta, Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseButtonNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rightMouseButtonNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // Shows the tool tip when the widget is located below the mouse.
        // Returns its tool tip or the tool tip from a child widget if the mouse is on top of the widget.
        // A nullptr is returned when the mouse is not on top of the widget or when the tool tip is empty.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr askToolTip(Vector2f mousePos) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool update(sf::Time elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // The function returns true when the event is consumed and false when the event was ignored by all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool handleEvent(sf::Event& event);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Checks above which widget the mouse is standing.
        // If there is no widget below the mouse then this function will return a null pointer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr mouseOnWhichWidget(Vector2f mousePos);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will call the draw function from all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void drawWidgetContainer(sf::RenderTarget* target, const sf::RenderStates& states = sf::RenderStates::Default) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Find out what the index of the focused widget is. Returns 0 when no widget is focused and index+1 otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getFocusedWidgetIndex() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Try to focus the given child widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool tryFocusWidget(const tgui::Widget::Ptr &widget, bool reverseWidgetOrder);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::vector<Widget::Ptr> m_widgets;

        Widget::Ptr m_widgetBelowMouse;
        Widget::Ptr m_focusedWidget;

        Vector2f m_prevInnerSize;

        // Did we enter handleEvent directly or because we got a MouseReleased event?
        bool m_handingMouseReleased = false;

        // Does focusing the next widget always keep a widget from this container focused (e.g. in a ChildWindow)?
        bool m_isolatedFocus = false;


        friend class SubwidgetContainer; // Needs access to save and load functions

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @internal
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API GuiContainer : public Container
    {
    public:

        typedef std::shared_ptr<GuiContainer> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const GuiContainer> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        GuiContainer();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Doesn't has any effect
        ///
        /// @param size  Ignored
        ///
        /// The window size cannot be changed by a widget.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focus or unfocus the widget
        /// @param focused  Is the widget focused?
        ///
        /// The gui container can't be unfocused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFocused(bool focused) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /// This function always returns true.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnWidget(Vector2f pos) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function does nothing.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns a nullptr.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return nullptr;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        friend class Gui; // Required to let Gui access protected members from container and Widget

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CONTAINER_HPP
