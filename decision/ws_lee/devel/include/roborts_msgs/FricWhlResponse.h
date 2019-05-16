// Generated by gencpp from file roborts_msgs/FricWhlResponse.msg
// DO NOT EDIT!


#ifndef ROBORTS_MSGS_MESSAGE_FRICWHLRESPONSE_H
#define ROBORTS_MSGS_MESSAGE_FRICWHLRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace roborts_msgs
{
template <class ContainerAllocator>
struct FricWhlResponse_
{
  typedef FricWhlResponse_<ContainerAllocator> Type;

  FricWhlResponse_()
    : received(false)  {
    }
  FricWhlResponse_(const ContainerAllocator& _alloc)
    : received(false)  {
  (void)_alloc;
    }



   typedef uint8_t _received_type;
  _received_type received;





  typedef boost::shared_ptr< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> const> ConstPtr;

}; // struct FricWhlResponse_

typedef ::roborts_msgs::FricWhlResponse_<std::allocator<void> > FricWhlResponse;

typedef boost::shared_ptr< ::roborts_msgs::FricWhlResponse > FricWhlResponsePtr;
typedef boost::shared_ptr< ::roborts_msgs::FricWhlResponse const> FricWhlResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::roborts_msgs::FricWhlResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace roborts_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/kinetic/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'roborts_msgs': ['/home/nvidia/Desktop/tae_han_test_final/devel/share/roborts_msgs/msg', '/home/nvidia/Desktop/tae_han_test_final/src/roborts_msgs/msg', '/home/nvidia/Desktop/tae_han_test_final/src/roborts_msgs/msg/referee_system'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dd4152e077925db952c78baadb1e48b7";
  }

  static const char* value(const ::roborts_msgs::FricWhlResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdd4152e077925db9ULL;
  static const uint64_t static_value2 = 0x52c78baadb1e48b7ULL;
};

template<class ContainerAllocator>
struct DataType< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "roborts_msgs/FricWhlResponse";
  }

  static const char* value(const ::roborts_msgs::FricWhlResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool received\n\
\n\
";
  }

  static const char* value(const ::roborts_msgs::FricWhlResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.received);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct FricWhlResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::roborts_msgs::FricWhlResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::roborts_msgs::FricWhlResponse_<ContainerAllocator>& v)
  {
    s << indent << "received: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.received);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBORTS_MSGS_MESSAGE_FRICWHLRESPONSE_H
