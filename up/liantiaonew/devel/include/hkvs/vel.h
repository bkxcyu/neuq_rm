// Generated by gencpp from file hkvs/vel.msg
// DO NOT EDIT!


#ifndef HKVS_MESSAGE_VEL_H
#define HKVS_MESSAGE_VEL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace hkvs
{
template <class ContainerAllocator>
struct vel_
{
  typedef vel_<ContainerAllocator> Type;

  vel_()
    : vel(0.0)  {
    }
  vel_(const ContainerAllocator& _alloc)
    : vel(0.0)  {
  (void)_alloc;
    }



   typedef float _vel_type;
  _vel_type vel;





  typedef boost::shared_ptr< ::hkvs::vel_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hkvs::vel_<ContainerAllocator> const> ConstPtr;

}; // struct vel_

typedef ::hkvs::vel_<std::allocator<void> > vel;

typedef boost::shared_ptr< ::hkvs::vel > velPtr;
typedef boost::shared_ptr< ::hkvs::vel const> velConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hkvs::vel_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hkvs::vel_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hkvs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'hkvs': ['/home/tyj/liantiaonew/src/hkvs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hkvs::vel_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hkvs::vel_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hkvs::vel_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hkvs::vel_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hkvs::vel_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hkvs::vel_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hkvs::vel_<ContainerAllocator> >
{
  static const char* value()
  {
    return "378ca590f55ecb8d30867c8ddf1db3c5";
  }

  static const char* value(const ::hkvs::vel_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x378ca590f55ecb8dULL;
  static const uint64_t static_value2 = 0x30867c8ddf1db3c5ULL;
};

template<class ContainerAllocator>
struct DataType< ::hkvs::vel_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hkvs/vel";
  }

  static const char* value(const ::hkvs::vel_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hkvs::vel_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 vel\n\
";
  }

  static const char* value(const ::hkvs::vel_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hkvs::vel_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.vel);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct vel_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hkvs::vel_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hkvs::vel_<ContainerAllocator>& v)
  {
    s << indent << "vel: ";
    Printer<float>::stream(s, indent + "  ", v.vel);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HKVS_MESSAGE_VEL_H
