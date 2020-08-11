#include "aes-ex.h"
#include <cstring>


/*
 * 注意：此代码没有防御AES定时攻击的能力
 */
AesEx::AesEx()
{
	this->generate_s_box();
}


AesEx::~AesEx()
{

}


void 
AesEx::generate_s_box()
{
	//避免s_box数据直接在PE文件中明文存储，使用QMap离散数据类型存储。减小反编译者查看s-box进而推测出加密方式的概率
	this->_s_box.insert(std::pair<int, u_char>(0, 0x63));
	this->_s_box.insert(std::pair<int, u_char>(1, 0x7c));
	this->_s_box.insert(std::pair<int, u_char>(2, 0x77));
	this->_s_box.insert(std::pair<int, u_char>(3, 0x7b));
	this->_s_box.insert(std::pair<int, u_char>(4, 0xf2));
	this->_s_box.insert(std::pair<int, u_char>(5, 0x6b));
	this->_s_box.insert(std::pair<int, u_char>(6, 0x6f));
	this->_s_box.insert(std::pair<int, u_char>(7, 0xc5));
	this->_s_box.insert(std::pair<int, u_char>(8, 0x30));
	this->_s_box.insert(std::pair<int, u_char>(9, 0x01));
	this->_s_box.insert(std::pair<int, u_char>(10, 0x67));
	this->_s_box.insert(std::pair<int, u_char>(11, 0x2b));
	this->_s_box.insert(std::pair<int, u_char>(12, 0xfe));
	this->_s_box.insert(std::pair<int, u_char>(13, 0xd7));
	this->_s_box.insert(std::pair<int, u_char>(14, 0xab));
	this->_s_box.insert(std::pair<int, u_char>(15, 0x76));
	this->_s_box.insert(std::pair<int, u_char>(16, 0xca));
	this->_s_box.insert(std::pair<int, u_char>(17, 0x82));
	this->_s_box.insert(std::pair<int, u_char>(18, 0xc9));
	this->_s_box.insert(std::pair<int, u_char>(19, 0x7d));
	this->_s_box.insert(std::pair<int, u_char>(20, 0xfa));
	this->_s_box.insert(std::pair<int, u_char>(21, 0x59));
	this->_s_box.insert(std::pair<int, u_char>(22, 0x47));
	this->_s_box.insert(std::pair<int, u_char>(23, 0xf0));
	this->_s_box.insert(std::pair<int, u_char>(24, 0xad));
	this->_s_box.insert(std::pair<int, u_char>(25, 0xd4));
	this->_s_box.insert(std::pair<int, u_char>(26, 0xa2));
	this->_s_box.insert(std::pair<int, u_char>(27, 0xaf));
	this->_s_box.insert(std::pair<int, u_char>(28, 0x9c));
	this->_s_box.insert(std::pair<int, u_char>(29, 0xa4));
	this->_s_box.insert(std::pair<int, u_char>(30, 0x72));
	this->_s_box.insert(std::pair<int, u_char>(31, 0xc0));
	this->_s_box.insert(std::pair<int, u_char>(32, 0xb7));
	this->_s_box.insert(std::pair<int, u_char>(33, 0xfd));
	this->_s_box.insert(std::pair<int, u_char>(34, 0x93));
	this->_s_box.insert(std::pair<int, u_char>(35, 0x26));
	this->_s_box.insert(std::pair<int, u_char>(36, 0x36));
	this->_s_box.insert(std::pair<int, u_char>(37, 0x3f));
	this->_s_box.insert(std::pair<int, u_char>(38, 0xf7));
	this->_s_box.insert(std::pair<int, u_char>(39, 0xcc));
	this->_s_box.insert(std::pair<int, u_char>(40, 0x34));
	this->_s_box.insert(std::pair<int, u_char>(41, 0xa5));
	this->_s_box.insert(std::pair<int, u_char>(42, 0xe5));
	this->_s_box.insert(std::pair<int, u_char>(43, 0xf1));
	this->_s_box.insert(std::pair<int, u_char>(44, 0x71));
	this->_s_box.insert(std::pair<int, u_char>(45, 0xd8));
	this->_s_box.insert(std::pair<int, u_char>(46, 0x31));
	this->_s_box.insert(std::pair<int, u_char>(47, 0x15));
	this->_s_box.insert(std::pair<int, u_char>(48, 0x04));
	this->_s_box.insert(std::pair<int, u_char>(49, 0xc7));
	this->_s_box.insert(std::pair<int, u_char>(50, 0x23));
	this->_s_box.insert(std::pair<int, u_char>(51, 0xc3));
	this->_s_box.insert(std::pair<int, u_char>(52, 0x18));
	this->_s_box.insert(std::pair<int, u_char>(53, 0x96));
	this->_s_box.insert(std::pair<int, u_char>(54, 0x05));
	this->_s_box.insert(std::pair<int, u_char>(55, 0x9a));
	this->_s_box.insert(std::pair<int, u_char>(56, 0x07));
	this->_s_box.insert(std::pair<int, u_char>(57, 0x12));
	this->_s_box.insert(std::pair<int, u_char>(58, 0x80));
	this->_s_box.insert(std::pair<int, u_char>(59, 0xe2));
	this->_s_box.insert(std::pair<int, u_char>(60, 0xeb));
	this->_s_box.insert(std::pair<int, u_char>(61, 0x27));
	this->_s_box.insert(std::pair<int, u_char>(62, 0xb2));
	this->_s_box.insert(std::pair<int, u_char>(63, 0x75));
	this->_s_box.insert(std::pair<int, u_char>(64, 0x09));
	this->_s_box.insert(std::pair<int, u_char>(65, 0x83));
	this->_s_box.insert(std::pair<int, u_char>(66, 0x2c));
	this->_s_box.insert(std::pair<int, u_char>(67, 0x1a));
	this->_s_box.insert(std::pair<int, u_char>(68, 0x1b));
	this->_s_box.insert(std::pair<int, u_char>(69, 0x6e));
	this->_s_box.insert(std::pair<int, u_char>(70, 0x5a));
	this->_s_box.insert(std::pair<int, u_char>(71, 0xa0));
	this->_s_box.insert(std::pair<int, u_char>(72, 0x52));
	this->_s_box.insert(std::pair<int, u_char>(73, 0x3b));
	this->_s_box.insert(std::pair<int, u_char>(74, 0xd6));
	this->_s_box.insert(std::pair<int, u_char>(75, 0xb3));
	this->_s_box.insert(std::pair<int, u_char>(76, 0x29));
	this->_s_box.insert(std::pair<int, u_char>(77, 0xe3));
	this->_s_box.insert(std::pair<int, u_char>(78, 0x2f));
	this->_s_box.insert(std::pair<int, u_char>(79, 0x84));
	this->_s_box.insert(std::pair<int, u_char>(80, 0x53));
	this->_s_box.insert(std::pair<int, u_char>(81, 0xd1));
	this->_s_box.insert(std::pair<int, u_char>(82, 0x00));
	this->_s_box.insert(std::pair<int, u_char>(83, 0xed));
	this->_s_box.insert(std::pair<int, u_char>(84, 0x20));
	this->_s_box.insert(std::pair<int, u_char>(85, 0xfc));
	this->_s_box.insert(std::pair<int, u_char>(86, 0xb1));
	this->_s_box.insert(std::pair<int, u_char>(87, 0x5b));
	this->_s_box.insert(std::pair<int, u_char>(88, 0x6a));
	this->_s_box.insert(std::pair<int, u_char>(89, 0xcb));
	this->_s_box.insert(std::pair<int, u_char>(90, 0xbe));
	this->_s_box.insert(std::pair<int, u_char>(91, 0x39));
	this->_s_box.insert(std::pair<int, u_char>(92, 0x4a));
	this->_s_box.insert(std::pair<int, u_char>(93, 0x4c));
	this->_s_box.insert(std::pair<int, u_char>(94, 0x58));
	this->_s_box.insert(std::pair<int, u_char>(95, 0xcf));
	this->_s_box.insert(std::pair<int, u_char>(96, 0xd0));
	this->_s_box.insert(std::pair<int, u_char>(97, 0xef));
	this->_s_box.insert(std::pair<int, u_char>(98, 0xaa));
	this->_s_box.insert(std::pair<int, u_char>(99, 0xfb));
	this->_s_box.insert(std::pair<int, u_char>(100, 0x43));
	this->_s_box.insert(std::pair<int, u_char>(101, 0x4d));
	this->_s_box.insert(std::pair<int, u_char>(102, 0x33));
	this->_s_box.insert(std::pair<int, u_char>(103, 0x85));
	this->_s_box.insert(std::pair<int, u_char>(104, 0x45));
	this->_s_box.insert(std::pair<int, u_char>(105, 0xf9));
	this->_s_box.insert(std::pair<int, u_char>(106, 0x02));
	this->_s_box.insert(std::pair<int, u_char>(107, 0x7f));
	this->_s_box.insert(std::pair<int, u_char>(108, 0x50));
	this->_s_box.insert(std::pair<int, u_char>(109, 0x3c));
	this->_s_box.insert(std::pair<int, u_char>(110, 0x9f));
	this->_s_box.insert(std::pair<int, u_char>(111, 0xa8));
	this->_s_box.insert(std::pair<int, u_char>(112, 0x51));
	this->_s_box.insert(std::pair<int, u_char>(113, 0xa3));
	this->_s_box.insert(std::pair<int, u_char>(114, 0x40));
	this->_s_box.insert(std::pair<int, u_char>(115, 0x8f));
	this->_s_box.insert(std::pair<int, u_char>(116, 0x92));
	this->_s_box.insert(std::pair<int, u_char>(117, 0x9d));
	this->_s_box.insert(std::pair<int, u_char>(118, 0x38));
	this->_s_box.insert(std::pair<int, u_char>(119, 0xf5));
	this->_s_box.insert(std::pair<int, u_char>(120, 0xbc));
	this->_s_box.insert(std::pair<int, u_char>(121, 0xb6));
	this->_s_box.insert(std::pair<int, u_char>(122, 0xda));
	this->_s_box.insert(std::pair<int, u_char>(123, 0x21));
	this->_s_box.insert(std::pair<int, u_char>(124, 0x10));
	this->_s_box.insert(std::pair<int, u_char>(125, 0xff));
	this->_s_box.insert(std::pair<int, u_char>(126, 0xf3));
	this->_s_box.insert(std::pair<int, u_char>(127, 0xd2));
	this->_s_box.insert(std::pair<int, u_char>(128, 0xcd));
	this->_s_box.insert(std::pair<int, u_char>(129, 0x0c));
	this->_s_box.insert(std::pair<int, u_char>(130, 0x13));
	this->_s_box.insert(std::pair<int, u_char>(131, 0xec));
	this->_s_box.insert(std::pair<int, u_char>(132, 0x5f));
	this->_s_box.insert(std::pair<int, u_char>(133, 0x97));
	this->_s_box.insert(std::pair<int, u_char>(134, 0x44));
	this->_s_box.insert(std::pair<int, u_char>(135, 0x17));
	this->_s_box.insert(std::pair<int, u_char>(136, 0xc4));
	this->_s_box.insert(std::pair<int, u_char>(137, 0xa7));
	this->_s_box.insert(std::pair<int, u_char>(138, 0x7e));
	this->_s_box.insert(std::pair<int, u_char>(139, 0x3d));
	this->_s_box.insert(std::pair<int, u_char>(140, 0x64));
	this->_s_box.insert(std::pair<int, u_char>(141, 0x5d));
	this->_s_box.insert(std::pair<int, u_char>(142, 0x19));
	this->_s_box.insert(std::pair<int, u_char>(143, 0x73));
	this->_s_box.insert(std::pair<int, u_char>(144, 0x60));
	this->_s_box.insert(std::pair<int, u_char>(145, 0x81));
	this->_s_box.insert(std::pair<int, u_char>(146, 0x4f));
	this->_s_box.insert(std::pair<int, u_char>(147, 0xdc));
	this->_s_box.insert(std::pair<int, u_char>(148, 0x22));
	this->_s_box.insert(std::pair<int, u_char>(149, 0x2a));
	this->_s_box.insert(std::pair<int, u_char>(150, 0x90));
	this->_s_box.insert(std::pair<int, u_char>(151, 0x88));
	this->_s_box.insert(std::pair<int, u_char>(152, 0x46));
	this->_s_box.insert(std::pair<int, u_char>(153, 0xee));
	this->_s_box.insert(std::pair<int, u_char>(154, 0xb8));
	this->_s_box.insert(std::pair<int, u_char>(155, 0x14));
	this->_s_box.insert(std::pair<int, u_char>(156, 0xde));
	this->_s_box.insert(std::pair<int, u_char>(157, 0x5e));
	this->_s_box.insert(std::pair<int, u_char>(158, 0x0b));
	this->_s_box.insert(std::pair<int, u_char>(159, 0xdb));
	this->_s_box.insert(std::pair<int, u_char>(160, 0xe0));
	this->_s_box.insert(std::pair<int, u_char>(161, 0x32));
	this->_s_box.insert(std::pair<int, u_char>(162, 0x3a));
	this->_s_box.insert(std::pair<int, u_char>(163, 0x0a));
	this->_s_box.insert(std::pair<int, u_char>(164, 0x49));
	this->_s_box.insert(std::pair<int, u_char>(165, 0x06));
	this->_s_box.insert(std::pair<int, u_char>(166, 0x24));
	this->_s_box.insert(std::pair<int, u_char>(167, 0x5c));
	this->_s_box.insert(std::pair<int, u_char>(168, 0xc2));
	this->_s_box.insert(std::pair<int, u_char>(169, 0xd3));
	this->_s_box.insert(std::pair<int, u_char>(170, 0xac));
	this->_s_box.insert(std::pair<int, u_char>(171, 0x62));
	this->_s_box.insert(std::pair<int, u_char>(172, 0x91));
	this->_s_box.insert(std::pair<int, u_char>(173, 0x95));
	this->_s_box.insert(std::pair<int, u_char>(174, 0xe4));
	this->_s_box.insert(std::pair<int, u_char>(175, 0x79));
	this->_s_box.insert(std::pair<int, u_char>(176, 0xe7));
	this->_s_box.insert(std::pair<int, u_char>(177, 0xc8));
	this->_s_box.insert(std::pair<int, u_char>(178, 0x37));
	this->_s_box.insert(std::pair<int, u_char>(179, 0x6d));
	this->_s_box.insert(std::pair<int, u_char>(180, 0x8d));
	this->_s_box.insert(std::pair<int, u_char>(181, 0xd5));
	this->_s_box.insert(std::pair<int, u_char>(182, 0x4e));
	this->_s_box.insert(std::pair<int, u_char>(183, 0xa9));
	this->_s_box.insert(std::pair<int, u_char>(184, 0x6c));
	this->_s_box.insert(std::pair<int, u_char>(185, 0x56));
	this->_s_box.insert(std::pair<int, u_char>(186, 0xf4));
	this->_s_box.insert(std::pair<int, u_char>(187, 0xea));
	this->_s_box.insert(std::pair<int, u_char>(188, 0x65));
	this->_s_box.insert(std::pair<int, u_char>(189, 0x7a));
	this->_s_box.insert(std::pair<int, u_char>(190, 0xae));
	this->_s_box.insert(std::pair<int, u_char>(191, 0x08));
	this->_s_box.insert(std::pair<int, u_char>(192, 0xba));
	this->_s_box.insert(std::pair<int, u_char>(193, 0x78));
	this->_s_box.insert(std::pair<int, u_char>(194, 0x25));
	this->_s_box.insert(std::pair<int, u_char>(195, 0x2e));
	this->_s_box.insert(std::pair<int, u_char>(196, 0x1c));
	this->_s_box.insert(std::pair<int, u_char>(197, 0xa6));
	this->_s_box.insert(std::pair<int, u_char>(198, 0xb4));
	this->_s_box.insert(std::pair<int, u_char>(199, 0xc6));
	this->_s_box.insert(std::pair<int, u_char>(200, 0xe8));
	this->_s_box.insert(std::pair<int, u_char>(201, 0xdd));
	this->_s_box.insert(std::pair<int, u_char>(202, 0x74));
	this->_s_box.insert(std::pair<int, u_char>(203, 0x1f));
	this->_s_box.insert(std::pair<int, u_char>(204, 0x4b));
	this->_s_box.insert(std::pair<int, u_char>(205, 0xbd));
	this->_s_box.insert(std::pair<int, u_char>(206, 0x8b));
	this->_s_box.insert(std::pair<int, u_char>(207, 0x8a));
	this->_s_box.insert(std::pair<int, u_char>(208, 0x70));
	this->_s_box.insert(std::pair<int, u_char>(209, 0x3e));
	this->_s_box.insert(std::pair<int, u_char>(210, 0xb5));
	this->_s_box.insert(std::pair<int, u_char>(211, 0x66));
	this->_s_box.insert(std::pair<int, u_char>(212, 0x48));
	this->_s_box.insert(std::pair<int, u_char>(213, 0x03));
	this->_s_box.insert(std::pair<int, u_char>(214, 0xf6));
	this->_s_box.insert(std::pair<int, u_char>(215, 0x0e));
	this->_s_box.insert(std::pair<int, u_char>(216, 0x61));
	this->_s_box.insert(std::pair<int, u_char>(217, 0x35));
	this->_s_box.insert(std::pair<int, u_char>(218, 0x57));
	this->_s_box.insert(std::pair<int, u_char>(219, 0xb9));
	this->_s_box.insert(std::pair<int, u_char>(220, 0x86));
	this->_s_box.insert(std::pair<int, u_char>(221, 0xc1));
	this->_s_box.insert(std::pair<int, u_char>(222, 0x1d));
	this->_s_box.insert(std::pair<int, u_char>(223, 0x9e));
	this->_s_box.insert(std::pair<int, u_char>(224, 0xe1));
	this->_s_box.insert(std::pair<int, u_char>(225, 0xf8));
	this->_s_box.insert(std::pair<int, u_char>(226, 0x98));
	this->_s_box.insert(std::pair<int, u_char>(227, 0x11));
	this->_s_box.insert(std::pair<int, u_char>(228, 0x69));
	this->_s_box.insert(std::pair<int, u_char>(229, 0xd9));
	this->_s_box.insert(std::pair<int, u_char>(230, 0x8e));
	this->_s_box.insert(std::pair<int, u_char>(231, 0x94));
	this->_s_box.insert(std::pair<int, u_char>(232, 0x9b));
	this->_s_box.insert(std::pair<int, u_char>(233, 0x1e));
	this->_s_box.insert(std::pair<int, u_char>(234, 0x87));
	this->_s_box.insert(std::pair<int, u_char>(235, 0xe9));
	this->_s_box.insert(std::pair<int, u_char>(236, 0xce));
	this->_s_box.insert(std::pair<int, u_char>(237, 0x55));
	this->_s_box.insert(std::pair<int, u_char>(238, 0x28));
	this->_s_box.insert(std::pair<int, u_char>(239, 0xdf));
	this->_s_box.insert(std::pair<int, u_char>(240, 0x8c));
	this->_s_box.insert(std::pair<int, u_char>(241, 0xa1));
	this->_s_box.insert(std::pair<int, u_char>(242, 0x89));
	this->_s_box.insert(std::pair<int, u_char>(243, 0x0d));
	this->_s_box.insert(std::pair<int, u_char>(244, 0xbf));
	this->_s_box.insert(std::pair<int, u_char>(245, 0xe6));
	this->_s_box.insert(std::pair<int, u_char>(246, 0x42));
	this->_s_box.insert(std::pair<int, u_char>(247, 0x68));
	this->_s_box.insert(std::pair<int, u_char>(248, 0x41));
	this->_s_box.insert(std::pair<int, u_char>(249, 0x99));
	this->_s_box.insert(std::pair<int, u_char>(250, 0x2d));
	this->_s_box.insert(std::pair<int, u_char>(251, 0x0f));
	this->_s_box.insert(std::pair<int, u_char>(252, 0xb0));
	this->_s_box.insert(std::pair<int, u_char>(253, 0x54));
	this->_s_box.insert(std::pair<int, u_char>(254, 0xbb));
	this->_s_box.insert(std::pair<int, u_char>(255, 0x16));
	
	this->_inverse_s_box.insert(std::pair<int, u_char>(0, 0x52));
	this->_inverse_s_box.insert(std::pair<int, u_char>(1, 0x09));
	this->_inverse_s_box.insert(std::pair<int, u_char>(2, 0x6a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(3, 0xd5));
	this->_inverse_s_box.insert(std::pair<int, u_char>(4, 0x30));
	this->_inverse_s_box.insert(std::pair<int, u_char>(5, 0x36));
	this->_inverse_s_box.insert(std::pair<int, u_char>(6, 0xa5));
	this->_inverse_s_box.insert(std::pair<int, u_char>(7, 0x38));
	this->_inverse_s_box.insert(std::pair<int, u_char>(8, 0xbf));
	this->_inverse_s_box.insert(std::pair<int, u_char>(9, 0x40));
	this->_inverse_s_box.insert(std::pair<int, u_char>(10, 0xa3));
	this->_inverse_s_box.insert(std::pair<int, u_char>(11, 0x9e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(12, 0x81));
	this->_inverse_s_box.insert(std::pair<int, u_char>(13, 0xf3));
	this->_inverse_s_box.insert(std::pair<int, u_char>(14, 0xd7));
	this->_inverse_s_box.insert(std::pair<int, u_char>(15, 0xfb));
	this->_inverse_s_box.insert(std::pair<int, u_char>(16, 0x7c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(17, 0xe3));
	this->_inverse_s_box.insert(std::pair<int, u_char>(18, 0x39));
	this->_inverse_s_box.insert(std::pair<int, u_char>(19, 0x82));
	this->_inverse_s_box.insert(std::pair<int, u_char>(20, 0x9b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(21, 0x2f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(22, 0xff));
	this->_inverse_s_box.insert(std::pair<int, u_char>(23, 0x87));
	this->_inverse_s_box.insert(std::pair<int, u_char>(24, 0x34));
	this->_inverse_s_box.insert(std::pair<int, u_char>(25, 0x8e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(26, 0x43));
	this->_inverse_s_box.insert(std::pair<int, u_char>(27, 0x44));
	this->_inverse_s_box.insert(std::pair<int, u_char>(28, 0xc4));
	this->_inverse_s_box.insert(std::pair<int, u_char>(29, 0xde));
	this->_inverse_s_box.insert(std::pair<int, u_char>(30, 0xe9));
	this->_inverse_s_box.insert(std::pair<int, u_char>(31, 0xcb));
	this->_inverse_s_box.insert(std::pair<int, u_char>(32, 0x54));
	this->_inverse_s_box.insert(std::pair<int, u_char>(33, 0x7b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(34, 0x94));
	this->_inverse_s_box.insert(std::pair<int, u_char>(35, 0x32));
	this->_inverse_s_box.insert(std::pair<int, u_char>(36, 0xa6));
	this->_inverse_s_box.insert(std::pair<int, u_char>(37, 0xc2));
	this->_inverse_s_box.insert(std::pair<int, u_char>(38, 0x23));
	this->_inverse_s_box.insert(std::pair<int, u_char>(39, 0x3d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(40, 0xee));
	this->_inverse_s_box.insert(std::pair<int, u_char>(41, 0x4c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(42, 0x95));
	this->_inverse_s_box.insert(std::pair<int, u_char>(43, 0x0b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(44, 0x42));
	this->_inverse_s_box.insert(std::pair<int, u_char>(45, 0xfa));
	this->_inverse_s_box.insert(std::pair<int, u_char>(46, 0xc3));
	this->_inverse_s_box.insert(std::pair<int, u_char>(47, 0x4e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(48, 0x08));
	this->_inverse_s_box.insert(std::pair<int, u_char>(49, 0x2e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(50, 0xa1));
	this->_inverse_s_box.insert(std::pair<int, u_char>(51, 0x66));
	this->_inverse_s_box.insert(std::pair<int, u_char>(52, 0x28));
	this->_inverse_s_box.insert(std::pair<int, u_char>(53, 0xd9));
	this->_inverse_s_box.insert(std::pair<int, u_char>(54, 0x24));
	this->_inverse_s_box.insert(std::pair<int, u_char>(55, 0xb2));
	this->_inverse_s_box.insert(std::pair<int, u_char>(56, 0x76));
	this->_inverse_s_box.insert(std::pair<int, u_char>(57, 0x5b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(58, 0xa2));
	this->_inverse_s_box.insert(std::pair<int, u_char>(59, 0x49));
	this->_inverse_s_box.insert(std::pair<int, u_char>(60, 0x6d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(61, 0x8b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(62, 0xd1));
	this->_inverse_s_box.insert(std::pair<int, u_char>(63, 0x25));
	this->_inverse_s_box.insert(std::pair<int, u_char>(64, 0x72));
	this->_inverse_s_box.insert(std::pair<int, u_char>(65, 0xf8));
	this->_inverse_s_box.insert(std::pair<int, u_char>(66, 0xf6));
	this->_inverse_s_box.insert(std::pair<int, u_char>(67, 0x64));
	this->_inverse_s_box.insert(std::pair<int, u_char>(68, 0x86));
	this->_inverse_s_box.insert(std::pair<int, u_char>(69, 0x68));
	this->_inverse_s_box.insert(std::pair<int, u_char>(70, 0x98));
	this->_inverse_s_box.insert(std::pair<int, u_char>(71, 0x16));
	this->_inverse_s_box.insert(std::pair<int, u_char>(72, 0xd4));
	this->_inverse_s_box.insert(std::pair<int, u_char>(73, 0xa4));
	this->_inverse_s_box.insert(std::pair<int, u_char>(74, 0x5c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(75, 0xcc));
	this->_inverse_s_box.insert(std::pair<int, u_char>(76, 0x5d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(77, 0x65));
	this->_inverse_s_box.insert(std::pair<int, u_char>(78, 0xb6));
	this->_inverse_s_box.insert(std::pair<int, u_char>(79, 0x92));
	this->_inverse_s_box.insert(std::pair<int, u_char>(80, 0x6c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(81, 0x70));
	this->_inverse_s_box.insert(std::pair<int, u_char>(82, 0x48));
	this->_inverse_s_box.insert(std::pair<int, u_char>(83, 0x50));
	this->_inverse_s_box.insert(std::pair<int, u_char>(84, 0xfd));
	this->_inverse_s_box.insert(std::pair<int, u_char>(85, 0xed));
	this->_inverse_s_box.insert(std::pair<int, u_char>(86, 0xb9));
	this->_inverse_s_box.insert(std::pair<int, u_char>(87, 0xda));
	this->_inverse_s_box.insert(std::pair<int, u_char>(88, 0x5e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(89, 0x15));
	this->_inverse_s_box.insert(std::pair<int, u_char>(90, 0x46));
	this->_inverse_s_box.insert(std::pair<int, u_char>(91, 0x57));
	this->_inverse_s_box.insert(std::pair<int, u_char>(92, 0xa7));
	this->_inverse_s_box.insert(std::pair<int, u_char>(93, 0x8d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(94, 0x9d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(95, 0x84));
	this->_inverse_s_box.insert(std::pair<int, u_char>(96, 0x90));
	this->_inverse_s_box.insert(std::pair<int, u_char>(97, 0xd8));
	this->_inverse_s_box.insert(std::pair<int, u_char>(98, 0xab));
	this->_inverse_s_box.insert(std::pair<int, u_char>(99, 0x00));
	this->_inverse_s_box.insert(std::pair<int, u_char>(100, 0x8c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(101, 0xbc));
	this->_inverse_s_box.insert(std::pair<int, u_char>(102, 0xd3));
	this->_inverse_s_box.insert(std::pair<int, u_char>(103, 0x0a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(104, 0xf7));
	this->_inverse_s_box.insert(std::pair<int, u_char>(105, 0xe4));
	this->_inverse_s_box.insert(std::pair<int, u_char>(106, 0x58));
	this->_inverse_s_box.insert(std::pair<int, u_char>(107, 0x05));
	this->_inverse_s_box.insert(std::pair<int, u_char>(108, 0xb8));
	this->_inverse_s_box.insert(std::pair<int, u_char>(109, 0xb3));
	this->_inverse_s_box.insert(std::pair<int, u_char>(110, 0x45));
	this->_inverse_s_box.insert(std::pair<int, u_char>(111, 0x06));
	this->_inverse_s_box.insert(std::pair<int, u_char>(112, 0xd0));
	this->_inverse_s_box.insert(std::pair<int, u_char>(113, 0x2c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(114, 0x1e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(115, 0x8f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(116, 0xca));
	this->_inverse_s_box.insert(std::pair<int, u_char>(117, 0x3f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(118, 0x0f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(119, 0x02));
	this->_inverse_s_box.insert(std::pair<int, u_char>(120, 0xc1));
	this->_inverse_s_box.insert(std::pair<int, u_char>(121, 0xaf));
	this->_inverse_s_box.insert(std::pair<int, u_char>(122, 0xbd));
	this->_inverse_s_box.insert(std::pair<int, u_char>(123, 0x03));
	this->_inverse_s_box.insert(std::pair<int, u_char>(124, 0x01));
	this->_inverse_s_box.insert(std::pair<int, u_char>(125, 0x13));
	this->_inverse_s_box.insert(std::pair<int, u_char>(126, 0x8a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(127, 0x6b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(128, 0x3a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(129, 0x91));
	this->_inverse_s_box.insert(std::pair<int, u_char>(130, 0x11));
	this->_inverse_s_box.insert(std::pair<int, u_char>(131, 0x41));
	this->_inverse_s_box.insert(std::pair<int, u_char>(132, 0x4f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(133, 0x67));
	this->_inverse_s_box.insert(std::pair<int, u_char>(134, 0xdc));
	this->_inverse_s_box.insert(std::pair<int, u_char>(135, 0xea));
	this->_inverse_s_box.insert(std::pair<int, u_char>(136, 0x97));
	this->_inverse_s_box.insert(std::pair<int, u_char>(137, 0xf2));
	this->_inverse_s_box.insert(std::pair<int, u_char>(138, 0xcf));
	this->_inverse_s_box.insert(std::pair<int, u_char>(139, 0xce));
	this->_inverse_s_box.insert(std::pair<int, u_char>(140, 0xf0));
	this->_inverse_s_box.insert(std::pair<int, u_char>(141, 0xb4));
	this->_inverse_s_box.insert(std::pair<int, u_char>(142, 0xe6));
	this->_inverse_s_box.insert(std::pair<int, u_char>(143, 0x73));
	this->_inverse_s_box.insert(std::pair<int, u_char>(144, 0x96));
	this->_inverse_s_box.insert(std::pair<int, u_char>(145, 0xac));
	this->_inverse_s_box.insert(std::pair<int, u_char>(146, 0x74));
	this->_inverse_s_box.insert(std::pair<int, u_char>(147, 0x22));
	this->_inverse_s_box.insert(std::pair<int, u_char>(148, 0xe7));
	this->_inverse_s_box.insert(std::pair<int, u_char>(149, 0xad));
	this->_inverse_s_box.insert(std::pair<int, u_char>(150, 0x35));
	this->_inverse_s_box.insert(std::pair<int, u_char>(151, 0x85));
	this->_inverse_s_box.insert(std::pair<int, u_char>(152, 0xe2));
	this->_inverse_s_box.insert(std::pair<int, u_char>(153, 0xf9));
	this->_inverse_s_box.insert(std::pair<int, u_char>(154, 0x37));
	this->_inverse_s_box.insert(std::pair<int, u_char>(155, 0xe8));
	this->_inverse_s_box.insert(std::pair<int, u_char>(156, 0x1c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(157, 0x75));
	this->_inverse_s_box.insert(std::pair<int, u_char>(158, 0xdf));
	this->_inverse_s_box.insert(std::pair<int, u_char>(159, 0x6e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(160, 0x47));
	this->_inverse_s_box.insert(std::pair<int, u_char>(161, 0xf1));
	this->_inverse_s_box.insert(std::pair<int, u_char>(162, 0x1a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(163, 0x71));
	this->_inverse_s_box.insert(std::pair<int, u_char>(164, 0x1d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(165, 0x29));
	this->_inverse_s_box.insert(std::pair<int, u_char>(166, 0xc5));
	this->_inverse_s_box.insert(std::pair<int, u_char>(167, 0x89));
	this->_inverse_s_box.insert(std::pair<int, u_char>(168, 0x6f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(169, 0xb7));
	this->_inverse_s_box.insert(std::pair<int, u_char>(170, 0x62));
	this->_inverse_s_box.insert(std::pair<int, u_char>(171, 0x0e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(172, 0xaa));
	this->_inverse_s_box.insert(std::pair<int, u_char>(173, 0x18));
	this->_inverse_s_box.insert(std::pair<int, u_char>(174, 0xbe));
	this->_inverse_s_box.insert(std::pair<int, u_char>(175, 0x1b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(176, 0xfc));
	this->_inverse_s_box.insert(std::pair<int, u_char>(177, 0x56));
	this->_inverse_s_box.insert(std::pair<int, u_char>(178, 0x3e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(179, 0x4b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(180, 0xc6));
	this->_inverse_s_box.insert(std::pair<int, u_char>(181, 0xd2));
	this->_inverse_s_box.insert(std::pair<int, u_char>(182, 0x79));
	this->_inverse_s_box.insert(std::pair<int, u_char>(183, 0x20));
	this->_inverse_s_box.insert(std::pair<int, u_char>(184, 0x9a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(185, 0xdb));
	this->_inverse_s_box.insert(std::pair<int, u_char>(186, 0xc0));
	this->_inverse_s_box.insert(std::pair<int, u_char>(187, 0xfe));
	this->_inverse_s_box.insert(std::pair<int, u_char>(188, 0x78));
	this->_inverse_s_box.insert(std::pair<int, u_char>(189, 0xcd));
	this->_inverse_s_box.insert(std::pair<int, u_char>(190, 0x5a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(191, 0xf4));
	this->_inverse_s_box.insert(std::pair<int, u_char>(192, 0x1f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(193, 0xdd));
	this->_inverse_s_box.insert(std::pair<int, u_char>(194, 0xa8));
	this->_inverse_s_box.insert(std::pair<int, u_char>(195, 0x33));
	this->_inverse_s_box.insert(std::pair<int, u_char>(196, 0x88));
	this->_inverse_s_box.insert(std::pair<int, u_char>(197, 0x07));
	this->_inverse_s_box.insert(std::pair<int, u_char>(198, 0xc7));
	this->_inverse_s_box.insert(std::pair<int, u_char>(199, 0x31));
	this->_inverse_s_box.insert(std::pair<int, u_char>(200, 0xb1));
	this->_inverse_s_box.insert(std::pair<int, u_char>(201, 0x12));
	this->_inverse_s_box.insert(std::pair<int, u_char>(202, 0x10));
	this->_inverse_s_box.insert(std::pair<int, u_char>(203, 0x59));
	this->_inverse_s_box.insert(std::pair<int, u_char>(204, 0x27));
	this->_inverse_s_box.insert(std::pair<int, u_char>(205, 0x80));
	this->_inverse_s_box.insert(std::pair<int, u_char>(206, 0xec));
	this->_inverse_s_box.insert(std::pair<int, u_char>(207, 0x5f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(208, 0x60));
	this->_inverse_s_box.insert(std::pair<int, u_char>(209, 0x51));
	this->_inverse_s_box.insert(std::pair<int, u_char>(210, 0x7f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(211, 0xa9));
	this->_inverse_s_box.insert(std::pair<int, u_char>(212, 0x19));
	this->_inverse_s_box.insert(std::pair<int, u_char>(213, 0xb5));
	this->_inverse_s_box.insert(std::pair<int, u_char>(214, 0x4a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(215, 0x0d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(216, 0x2d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(217, 0xe5));
	this->_inverse_s_box.insert(std::pair<int, u_char>(218, 0x7a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(219, 0x9f));
	this->_inverse_s_box.insert(std::pair<int, u_char>(220, 0x93));
	this->_inverse_s_box.insert(std::pair<int, u_char>(221, 0xc9));
	this->_inverse_s_box.insert(std::pair<int, u_char>(222, 0x9c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(223, 0xef));
	this->_inverse_s_box.insert(std::pair<int, u_char>(224, 0xa0));
	this->_inverse_s_box.insert(std::pair<int, u_char>(225, 0xe0));
	this->_inverse_s_box.insert(std::pair<int, u_char>(226, 0x3b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(227, 0x4d));
	this->_inverse_s_box.insert(std::pair<int, u_char>(228, 0xae));
	this->_inverse_s_box.insert(std::pair<int, u_char>(229, 0x2a));
	this->_inverse_s_box.insert(std::pair<int, u_char>(230, 0xf5));
	this->_inverse_s_box.insert(std::pair<int, u_char>(231, 0xb0));
	this->_inverse_s_box.insert(std::pair<int, u_char>(232, 0xc8));
	this->_inverse_s_box.insert(std::pair<int, u_char>(233, 0xeb));
	this->_inverse_s_box.insert(std::pair<int, u_char>(234, 0xbb));
	this->_inverse_s_box.insert(std::pair<int, u_char>(235, 0x3c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(236, 0x83));
	this->_inverse_s_box.insert(std::pair<int, u_char>(237, 0x53));
	this->_inverse_s_box.insert(std::pair<int, u_char>(238, 0x99));
	this->_inverse_s_box.insert(std::pair<int, u_char>(239, 0x61));
	this->_inverse_s_box.insert(std::pair<int, u_char>(240, 0x17));
	this->_inverse_s_box.insert(std::pair<int, u_char>(241, 0x2b));
	this->_inverse_s_box.insert(std::pair<int, u_char>(242, 0x04));
	this->_inverse_s_box.insert(std::pair<int, u_char>(243, 0x7e));
	this->_inverse_s_box.insert(std::pair<int, u_char>(244, 0xba));
	this->_inverse_s_box.insert(std::pair<int, u_char>(245, 0x77));
	this->_inverse_s_box.insert(std::pair<int, u_char>(246, 0xd6));
	this->_inverse_s_box.insert(std::pair<int, u_char>(247, 0x26));
	this->_inverse_s_box.insert(std::pair<int, u_char>(248, 0xe1));
	this->_inverse_s_box.insert(std::pair<int, u_char>(249, 0x69));
	this->_inverse_s_box.insert(std::pair<int, u_char>(250, 0x14));
	this->_inverse_s_box.insert(std::pair<int, u_char>(251, 0x63));
	this->_inverse_s_box.insert(std::pair<int, u_char>(252, 0x55));
	this->_inverse_s_box.insert(std::pair<int, u_char>(253, 0x21));
	this->_inverse_s_box.insert(std::pair<int, u_char>(254, 0x0c));
	this->_inverse_s_box.insert(std::pair<int, u_char>(255, 0x7d));

	this->_rcon.insert(std::pair<int, u_char>(0, 0x00));
	this->_rcon.insert(std::pair<int, u_char>(1, 0x01));
	this->_rcon.insert(std::pair<int, u_char>(2, 0x02));
	this->_rcon.insert(std::pair<int, u_char>(3, 0x04));
	this->_rcon.insert(std::pair<int, u_char>(4, 0x08));
	this->_rcon.insert(std::pair<int, u_char>(5, 0x10));
	this->_rcon.insert(std::pair<int, u_char>(6, 0x20));
	this->_rcon.insert(std::pair<int, u_char>(7, 0x40));
	this->_rcon.insert(std::pair<int, u_char>(8, 0x80));
	this->_rcon.insert(std::pair<int, u_char>(9, 0x1B));
	this->_rcon.insert(std::pair<int, u_char>(10, 0x36));
}


//debugged
void
AesEx::filling()
{
	this->_ciphertext = this->_plaintext;

	if (this->_plaintext.size() % 16 == 0)
	{

		u_char n = 16;
		for (int i = 0; i < n; i++)
		{

			std::string temp_str((char *)&n, 1);
			this->_ciphertext.append(temp_str);

		}

		return;

	}

	int n = 16 - this->_plaintext.size() % 16;
	u_char i = 0;

	for (i = 0; i < n; i++)
	{

		std::string temp_str((char *)&n, 1);
		this->_ciphertext.append(temp_str);

	}

RETURN:
	return ;
}


//debugged
void
AesEx::sub_bytes()
{
	int i = 0;

	for (i = 0; i < this->_ciphertext.size(); i++)
	{

		char c = this->_s_box[(u_char)this->_ciphertext.at(i)];
		this->_ciphertext[i] = c;

	}
}


void
AesEx::shift_rows()
{
	int a[] = {0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11};
	for (int block = 0; block < this->_ciphertext.size() / 16; block++)
	{

		int block_begin = block * 16;
		std::string after_shift_rows;
		for (int i = 0; i < 16; i++)
		{

			after_shift_rows.append(&this->_ciphertext.at(block_begin + a[i]), 1);

		}

		for (int i = 0; i < 16; i++)
		{

			this->_ciphertext[i + block_begin] = after_shift_rows.at(i);

		}

	}
}


void
AesEx::mix_columns()
{
	for (int j = 0; j < this->_ciphertext.size() / 16; j++)
	{

		for (int i = 0; i < 4; i++)
		{

			int block_size = j * 16;
			int index = block_size + i * 4;

			char temp0 = (char)(gmul(2, (u_char)this->_ciphertext.at(index)) 
				^ gmul(3, (u_char)this->_ciphertext.at(index + 1)) 
				^ (u_char)this->_ciphertext.at(index + 2) 
				^ (u_char)this->_ciphertext.at(index + 3));

			char temp1 = (char)((u_char)this->_ciphertext.at(index) 
				^ gmul(2, (u_char)this->_ciphertext.at(index + 1)) 
				^ gmul(3, (u_char)this->_ciphertext.at(index + 2)) 
				^ (u_char)this->_ciphertext.at(index + 3));
			
			char temp2 = (char)((u_char)this->_ciphertext.at(index) 
				^ (u_char)this->_ciphertext.at(index + 1) 
				^ gmul(2, (u_char)this->_ciphertext.at(index + 2)) 
				^ gmul(3, (u_char)this->_ciphertext.at(index + 3)));

			char temp3 = (char)(gmul(3, (u_char)this->_ciphertext.at(index)) 
				^ (u_char)this->_ciphertext.at(index + 1) 
				^ (u_char)this->_ciphertext.at(index + 2) 
				^ gmul(2, (u_char)this->_ciphertext.at(index + 3)));

			this->_ciphertext[index + 0] = temp0;
			this->_ciphertext[index + 1] = temp1;
			this->_ciphertext[index + 2] = temp2;
			this->_ciphertext[index + 3] = temp3;

		}

	}
}

void
AesEx::add_round_key(int n)
{
	int index = n * 16;
	int i;
	int j;

	for (j = 0; j < this->_ciphertext.size() / 16; j++)
	{

		for (i = index; i < index + 16; i++)
		{

			char temp_char = (char)((u_char)this->_key.at(i) ^ (u_char)this->_ciphertext.at(j * 16 + i - index));

			this->_ciphertext[j * 16 + i - index] = temp_char;

		}

	}
}


void
AesEx::encrypt(std::string __OUT__ &out)
{
	int i = 0;

	this->filling();

	this->add_round_key(0);

	for (i = 0; i < 13; i++)
	{
	
		this->sub_bytes();

		this->shift_rows();

		this->mix_columns();

		this->add_round_key(i + 1);
	
	}

	this->sub_bytes();

	this->shift_rows();

	this->add_round_key(14);

	out = this->_ciphertext;
}


//debugged
std::string
AesEx::gadd(int a, int b)
{
	std::string ret = "";
	a = a * 4;
	b = b * 4;

	for (int i = 0; i < 4; i++)
	{

		char temp_char = (char)((u_char)this->_key.at(a + i) ^ (u_char)this->_key.at(b + i));
		ret.append(&temp_char, 1);

	}
	
	return ret;
}


//debugged
std::string
AesEx::gadd(int a, std::string b)
{
	std::string ret = "";
	a = a * 4;

	for (int i = 0; i < 4; i++)
	{

		char temp_char = (char)((u_char)this->_key.at(a + i) ^ (u_char)b.at(i));
		ret.append(&temp_char, 1);

	}
	
	return ret;
}


//debugged
std::string
AesEx::gadd(std::string a, u_char b)
{
	char temp_char = (char)((u_char)a.at(0) ^ b);
	a[0] = temp_char;

	return a;
}


//debugged
std::string
AesEx::sub_word(std::string a)
{
	for (int i = 0; i < 4; i++)
	{

		char temp_char = (char)this->_s_box[(u_char)a.at(i)];
		a[i] = temp_char;

	}

	return a;
}


//debugged
std::string
AesEx::sub_word(int a)
{
	a = a * 4;
	std::string ret = "";
	for (int i = 0; i < 4; i++)
	{

		char temp_char = this->_s_box[(u_char)this->_key.at(a + i)];
		ret.append(&temp_char, 1);

	}

	return ret;
}


//debugged
std::string
AesEx::rot_word(int a)
{
	a = a * 4;
	char first_byte = this->_key.at(a);
	std::string ret = "";

	for (int i = 1; i < 4; i++)
	{

		ret.append(&this->_key.at(a + i), 1);
	
	}

	ret.append(&first_byte, 1);

	return ret;
}


//debugged
void
AesEx::set_key(const std::string &key)
{
	this->_key = key;
	
	for (int i = 8; i < 60; i++)
	{

		if ( i % 8 == 0)
		{

			std::string w = this->gadd(this->gadd(i - 8, this->sub_word(this->rot_word(i - 1))), this->_rcon[i / 8]);
			this->_key.append(w);

		} else if (i % 8 == 4) {
		
			std::string w = this->gadd(i - 8, this->sub_word(i - 1));
			this->_key.append(w);

		} else {

			std::string w = this->gadd(i - 8, i - 1);
			this->_key.append(w);

		}
	
	}
}
