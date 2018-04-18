#include <boost/python.hpp>
#include "pocket_dispatcher.h"

char const* yay()
{
	return "Yay!";
}

BOOST_PYTHON_MODULE(libpocket)
{
	using namespace boost::python;
		def("yay", yay);
		class_<PocketDispatcher>("PocketDispatcher")
			.def("Initialize", &PocketDispatcher::Initialize)
			.def("MakeDir", &PocketDispatcher::MakeDir)
			.def("Lookup", &PocketDispatcher::Lookup)
			.def("Enumerate", &PocketDispatcher::Enumerate)
			.def("PutFile", &PocketDispatcher::PutFile)
			.def("GetFile", &PocketDispatcher::GetFile)
			.def("DeleteFile", &PocketDispatcher::DeleteFile)
			.def("DeleteDir", &PocketDispatcher::DeleteDir)
		;

	
}
