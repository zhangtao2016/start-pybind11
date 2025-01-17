#include <pybind11/pybind11.h>
#include <pybind11/chrono.h>
#include <pybind11/functional.h>

#include <memory>

#include "cpp/cpp_thread_callback/tick.h"

namespace py = pybind11;
using namespace pybind11::literals;  // NOLINT

PYBIND11_MODULE(tick_pb, m) {
  m.doc() = "tick_pb bindings";

  py::class_<Tick, std::shared_ptr<Tick>>(m, "Tick")
    .def(py::init<std::int64_t, std::int64_t>())
    .def(py::init<TickEvent, std::int64_t, std::int64_t,
                  TickRunCallback, TickRunCallback>())
    .def_property_readonly("is_running", &Tick::IsRunning)
    .def("start", &Tick::Start, "", py::arg("delay_ms") = 1)
    .def("stop", &Tick::Stop, "wait_life_over"_a = false)
    .def("get_time_start", &Tick::GetTimeStart)
    .def("set_tick_event", [](Tick &self, const TickEvent &tick_event) {
      self.SetTickEvent(tick_event);
    })
    .def("set_run_beg_callback", [](Tick &self,
        const TickRunCallback &run_beg) {
      self.SetRunBegCallback(run_beg);
    })
    .def("set_run_end_callback", [](Tick &self,
        const TickRunCallback &run_end) {
      self.SetRunEndCallback(run_end);
    })
    .def("wait_life_over", &Tick::WaitLifeOver,
        py::call_guard<py::gil_scoped_release>());
}
