/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_TEXTURE_HPP
#define TGUI_TEXTURE_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TGUI/TextureData.hpp>
#include <TGUI/Global.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// TODO: Add documentation to functions

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Texture : public sf::Transformable, public sf::Drawable
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Texture() {}

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Texture(const Texture& copy);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ~Texture();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Texture& operator=(const Texture& right);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setTexture(TextureData& data, const sf::IntRect& middleRect);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        TextureData* getData() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setSize(const sf::Vector2f& size);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f getSize() const
        {
            return m_size;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2f getImageSize() const
        {
            return (m_data) ? sf::Vector2f{m_data->texture.getSize()} : sf::Vector2f{0,0};
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setColor(const sf::Color& color);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void setTextureRect(const sf::FloatRect& textureRect)
        {
            m_textureRect = textureRect;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enable or disable the smooth filter.
        ///
        /// When the filter is activated, the texture appears smoother so that pixels are less noticeable.
        /// However if you want the texture to look exactly the same as its source file, you should leave it disabled.
        /// The smooth filter is disabled by default.
        ///
        /// @param smooth True to enable smoothing, false to disable it
        ///
        /// @see isSmooth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSmooth(bool smooth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Tell whether the smooth filter is enabled or not.
        ///
        /// @return True if smoothing is enabled, false if it is disabled
        ///
        /// @see setSmooth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isSmooth() const
        {
            return (m_data) ? m_data->texture.isSmooth() : false;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bool isTransparentPixel(float x, float y) const;


    private:
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void updateVertices();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        enum ScalingType
        {
            Normal,
            Horizontal,
            Vertical,
            NineSliceScaling
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:
        TextureData* m_data = nullptr;
        std::vector<sf::Vertex> m_vertices;

        sf::Vector2f  m_size;
        sf::IntRect   m_middleRect;
        sf::FloatRect m_textureRect;

        ScalingType   m_scalingType = Normal;

        float m_rotation = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXTURE_HPP
