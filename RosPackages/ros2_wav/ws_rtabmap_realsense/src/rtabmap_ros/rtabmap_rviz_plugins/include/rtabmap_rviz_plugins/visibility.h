// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RTABMAP_RVIZ_PLUGINS__VISIBILITY_CONTROL_H_
#define RTABMAP_RVIZ_PLUGINS__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define RTABMAP_RVIZ_PLUGINS_EXPORT __attribute__ ((dllexport))
    #define RTABMAP_RVIZ_PLUGINS_IMPORT __attribute__ ((dllimport))
  #else
    #define RTABMAP_RVIZ_PLUGINS_EXPORT __declspec(dllexport)
    #define RTABMAP_RVIZ_PLUGINS_IMPORT __declspec(dllimport)
  #endif
  #ifdef RTABMAP_RVIZ_PLUGINS_BUILDING_DLL
    #define RTABMAP_RVIZ_PLUGINS_PUBLIC RTABMAP_RVIZ_PLUGINS_EXPORT
  #else
    #define RTABMAP_RVIZ_PLUGINS_PUBLIC RTABMAP_RVIZ_PLUGINS_IMPORT
  #endif
  #define RTABMAP_RVIZ_PLUGINS_PUBLIC_TYPE RTABMAP_RVIZ_PLUGINS_PUBLIC
  #define RTABMAP_RVIZ_PLUGINS_LOCAL
#else
  #define RTABMAP_RVIZ_PLUGINS_EXPORT __attribute__ ((visibility("default")))
  #define RTABMAP_RVIZ_PLUGINS_IMPORT
  #if __GNUC__ >= 4
    #define RTABMAP_RVIZ_PLUGINS_PUBLIC __attribute__ ((visibility("default")))
    #define RTABMAP_RVIZ_PLUGINS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define RTABMAP_RVIZ_PLUGINS_PUBLIC
    #define RTABMAP_RVIZ_PLUGINS_LOCAL
  #endif
  #define RTABMAP_RVIZ_PLUGINS_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // RTABMAP_RVIZ_PLUGINS__VISIBILITY_CONTROL_H_
