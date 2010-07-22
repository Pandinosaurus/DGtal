#pragma once

/**
 * @file ColorBrightnessColorMap.h
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/19
 *
 * Header file for module ColorBrightnessColorMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ColorBrightnessColorMap_RECURSES)
#error Recursive header files inclusion detected in ColorBrightnessColorMap.h
#else // defined(ColorBrightnessColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ColorBrightnessColorMap_RECURSES

#if !defined ColorBrightnessColorMap_h
/** Prevents repeated inclusion of headers. */
#define ColorBrightnessColorMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "Board/Board.h"
#include "Board/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ColorBrightnessColorMap
  /**
   * Description of template class 'ColorBrightnessColorMap' <p>
   * \brief Aim: This class template may be used to (linearly) convert scalar
   * values in a given range into a color with given lightness.
   * 
   * The ColorBrightnessColorMap can be used either as a functor object
   * (the value range is given at the object's construction, together with the
   * reference color) which converts a value into a LibBoard::Color structure,
   * or it can be used through a static method taking both the range and the
   * value as parameters.
   *
   * The code below shows a possible use of this class.
   * @code
   * #include "Board/Color.h"
   * #include "ColorBrightnessColorMap.h"
   * // ...
   * {
   *   ColorBrightnessColorMap<float> blueShade(0.0f,1.0f,LibBoard::Color::Blue);
   *   LibBoard::Color red = blueShade(1.0f);
   *   LibBoard::Color blue1 = blueShade(0.5f);
   *   // Or, equivalently:
   *   LibBoard::Color blue2 = ColorBrightnessColorMap<float>::getColor(LibBoard::Color::Blue,0.0f,1.0f,0.5f);
   * }
   * @endcode
   *
   * @tparam ValueType The type of the range values.
   */
  template <typename PValueType>
  class ColorBrightnessColorMap
  {
  public:
    
    typedef PValueType ValueType;

    // ----------------------- Standard services ------------------------------
  public:

    /** 
     * Constructor.
     * 
     * @param min The lower bound of the value range.
     * @param max The upper bound of the value range.
     */
    ColorBrightnessColorMap( const PValueType & min,
			     const PValueType & max,
			     const LibBoard::Color & color );
    
    /** 
     * Computes the color associated with a value in a given range.
     * 
     * @param value A value within the value range.
     * @return A color whose brightness linearly depends on the 
     * position of [value] within the current range.
     */
    LibBoard::Color operator()( const PValueType & value ) const;
      
    /**
     * Destructor.
     */
    ~ColorBrightnessColorMap();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    ColorBrightnessColorMap ( const ColorBrightnessColorMap & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    ColorBrightnessColorMap & operator= ( const ColorBrightnessColorMap & other );

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /** 
     * Returns the lower bound of the value range.
     *
     * @return The lower bound of the value range.
     */
    const PValueType & min() const;

    /** 
     * Returns the upper bound of the value range.
     *
     * @return The upper bound of the value range.
     */
    const PValueType & max() const;

    // ----------------------- Static methods ---------------------------------


    /** 
     * Computes the color associated with a value in a given range.
     * 
     * @param color The color associated with the upper bound. 
     * @param min The lower bound of the value range.  
     * @param max The upper bound of the value range.
     * @param value A value within the value range.
     * @return A color whose brightness linearly depends on the 
     * position of [value] within the range [min]..[max]. 
     */
    static LibBoard::Color getColor( const LibBoard::Color color,
				     const PValueType & min,
				     const PValueType & max,
				     const PValueType & value );
    
    // ------------------------- Protected Datas ------------------------------
  private:

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    PValueType myMin;		/**< The lower bound of the value range.  */
    PValueType myMax;            /**< The lower bound of the value range.  */
    LibBoard::Color myColor;	/**< The color of the upper bound value. */
    
    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    ColorBrightnessColorMap();

    // ------------------------- Internals ------------------------------------
  private:

    /** 
     * Converts a color from the HSV (Hue,Saturation,Value) space to the RGB space.
     * 
     * @param r The red component (out).
     * @param g The green component (out).
     * @param b The blue component (out).
     * @param h The hue of the color in [0..360)
     * @param s The saturation of the color in [0..1].
     * @param v The value of the color in [0..1].
     */
    static void HSVtoRGB( double & r, double & g, double & b,
			  double h, const double s, const double v);

    /** 
     * Converts a color from the RGB space to the HSV (Hue,Saturation,Value) space.
     * 
     * @param h (out) The hue of the color in [0..360)
     * @param s (out) The saturation of the color in [0..1].
     * @param v (out) The value of the color in [0..1].
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     */
    static void RGBtoHSV( double & h, double & s, double & v,
			  const unsigned char r,
			  const unsigned char g,
			  const unsigned char b );

  }; // end of class ColorBrightnessColorMap


  /**
   * Overloads 'operator<<' for displaying objects of class 'ColorBrightnessColorMap'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ColorBrightnessColorMap' to write.
   * @return the output stream after the writing.
   */
  template <typename PValueType>
  std::ostream&
  operator<< ( std::ostream & out, const ColorBrightnessColorMap<PValueType> & object );
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/colormaps/ColorBrightnessColorMap.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ColorBrightnessColorMap_h

#undef ColorBrightnessColorMap_RECURSES
#endif // else defined(ColorBrightnessColorMap_RECURSES)
