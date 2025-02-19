//==============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//  
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin.
//  Copyright 2004-2020, The Board of Regents of The University of Texas System
//
//==============================================================================

//==============================================================================
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin, under contract to an agency or agencies
//  within the U.S. Department of Defense. The U.S. Government retains all
//  rights to use, duplicate, distribute, disclose, or release this software.
//
//  Pursuant to DoD Directive 523024 
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public 
//                            release, distribution is unlimited.
//
//==============================================================================

/**
 * @file TimeNamedFileStream.hpp
 * Writes data to a file whose name is derived from a pattern and a nominal epoch. 
 */

#ifndef GPSTK_TIME_NAMED_FILE_STREAM_HPP
#define GPSTK_TIME_NAMED_FILE_STREAM_HPP

#include <string>

#include "Exception.hpp"
#include "CommonTime.hpp"
#include "SystemTime.hpp"
#include "FFStream.hpp"
#include "TimeString.hpp"
#include "FileUtils.hpp"

namespace gpstk
{
   /// @ingroup FFStream 
   //@{

   template <class BaseStream>
   class TimeNamedFileStream : public BaseStream
   {
   public:

      TimeNamedFileStream() 
         : omode(std::ios::in), debugLevel(0)
      {}
      TimeNamedFileStream(
         const std::string fs,
         std::ios::openmode mode = std::ios::in)
         : debugLevel(0), filespec(fs), omode(mode)
      {}
      virtual ~TimeNamedFileStream(void) {};


      /// overrides open to just set the filespec, Note that this does
      /// not actually open a file
      virtual void open(const char* fs, std::ios::openmode mode = std::ios::in)
      {
         setFilespec(fs);
         omode = mode;
      }


      void setFilespec(const std::string fs)
      { filespec=fs; currentFilename=""; }


      std::string getFilespec(void) const
      { return filespec; }


      // Get the filename of the current file
      std::string getCurrentFilename(void) const 
      { return currentFilename; }


      // Return the time used to generate the current file name
      CommonTime getCurrentTime(void) const
      { return currentTime; }


      // Update the file name, returns true if the file name changed
      bool updateFileName(const CommonTime& t=SystemTime())
      {
         const std::string newFilename=printTime(t,filespec);
         if (currentFilename.size() > 0 and newFilename == currentFilename)
         {
            currentTime = t;
            return false;
         }
         
         if (currentFilename.size() > 0)
         {
            if (debugLevel)
               std::cout << "Closing " << currentFilename << std::endl;
            BaseStream::close();
         }
         currentFilename = newFilename;
         currentTime = t;
         
         std::string::size_type i = newFilename.rfind('/');
         std::string dir(newFilename.substr(0, i));
         if (dir.size())
         {
            if (debugLevel)
               std::cout << "Creating directory " << dir << std::endl;
            gpstk::FileUtils::makeDir(dir, 0755);
         }
         
         BaseStream::open(currentFilename.c_str(), omode);
         if (debugLevel)
            std::cout << "Opened " << currentFilename << std::endl;
         
         return true;
      }

      int debugLevel;

   private:
      /// Pattern on which to create new files
      std::string filespec;
      
      /// Name of the current output file.
      std::string currentFilename;

      /// The time used to generate currentFilename
      CommonTime currentTime;

      // The flags to use when opening the files
      std::ios::openmode omode;
   }; // end class TimeNamedFileStream

   //@}
}  // end namespace gpstk

#endif // GPSTK_TIME_NAMED_FILE_STREAM_HPP
