/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include <model/WaterHeaterHeatPump.hpp>
#include <model/WaterHeaterHeatPump_Impl.hpp>
#include <model/Model.hpp>
#include <model/Model_Impl.hpp>
#include <model/WaterHeaterMixed.hpp>
#include <model/WaterHeaterMixed_Impl.hpp>
#include <model/FanOnOff.hpp>
#include <model/FanOnOff_Impl.hpp>
#include <model/CoilWaterHeatingAirToWaterHeatPump.hpp>
#include <model/CoilWaterHeatingAirToWaterHeatPump_Impl.hpp>
#include <model/Schedule.hpp>
#include <model/Schedule_Impl.hpp>
#include <model/ScheduleDay.hpp>
#include <model/ScheduleDay_Impl.hpp>
#include <model/HVACComponent.hpp>
#include <model/HVACComponent_Impl.hpp>
#include <model/ScheduleRuleset.hpp>
#include <model/ScheduleRuleset_Impl.hpp>
#include <model/ScheduleTypeLimits.hpp>
#include <model/ScheduleTypeRegistry.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/OS_WaterHeater_HeatPump_FieldEnums.hxx>
#include <utilities/units/Unit.hpp>
#include <utilities/core/Assert.hpp>

namespace openstudio {
namespace model {

namespace detail {

  WaterHeaterHeatPump_Impl::WaterHeaterHeatPump_Impl(const IdfObject& idfObject,
                                                     Model_Impl* model,
                                                     bool keepHandle)
    : ZoneHVACComponent_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == WaterHeaterHeatPump::iddObjectType());
  }

  WaterHeaterHeatPump_Impl::WaterHeaterHeatPump_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                     Model_Impl* model,
                                                     bool keepHandle)
    : ZoneHVACComponent_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == WaterHeaterHeatPump::iddObjectType());
  }

  WaterHeaterHeatPump_Impl::WaterHeaterHeatPump_Impl(const WaterHeaterHeatPump_Impl& other,
                                                     Model_Impl* model,
                                                     bool keepHandle)
    : ZoneHVACComponent_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& WaterHeaterHeatPump_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType WaterHeaterHeatPump_Impl::iddObjectType() const {
    return WaterHeaterHeatPump::iddObjectType();
  }

  std::vector<ScheduleTypeKey> WaterHeaterHeatPump_Impl::getScheduleTypeKeys(const Schedule& schedule) const
  {
    // TODO: Check schedule display names.
    std::vector<ScheduleTypeKey> result;
    UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
    UnsignedVector::const_iterator b(fieldIndices.begin()), e(fieldIndices.end());
    if (std::find(b,e,OS_WaterHeater_HeatPumpFields::AvailabilitySchedule) != e)
    {
      result.push_back(ScheduleTypeKey("WaterHeaterHeatPump","Availability Schedule"));
    }
    if (std::find(b,e,OS_WaterHeater_HeatPumpFields::CompressorSetpointTemperatureSchedule) != e)
    {
      result.push_back(ScheduleTypeKey("WaterHeaterHeatPump","Compressor Setpoint Temperature Schedule"));
    }
    if (std::find(b,e,OS_WaterHeater_HeatPumpFields::InletAirTemperatureSchedule) != e)
    {
      result.push_back(ScheduleTypeKey("WaterHeaterHeatPump","Inlet Air Temperature Schedule"));
    }
    if (std::find(b,e,OS_WaterHeater_HeatPumpFields::InletAirHumiditySchedule) != e)
    {
      result.push_back(ScheduleTypeKey("WaterHeaterHeatPump","Inlet Air Humidity Schedule"));
    }
    if (std::find(b,e,OS_WaterHeater_HeatPumpFields::CompressorAmbientTemperatureSchedule) != e)
    {
      result.push_back(ScheduleTypeKey("WaterHeaterHeatPump","Compressor Ambient Temperature Schedule"));
    }
    if (std::find(b,e,OS_WaterHeater_HeatPumpFields::InletAirMixerSchedule) != e)
    {
      result.push_back(ScheduleTypeKey("WaterHeaterHeatPump","Inlet Air Mixer Schedule"));
    }
    return result;
  }

  boost::optional<Schedule> WaterHeaterHeatPump_Impl::availabilitySchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_WaterHeater_HeatPumpFields::AvailabilitySchedule);
  }

  Schedule WaterHeaterHeatPump_Impl::compressorSetpointTemperatureSchedule() const {
    boost::optional<Schedule> value = optionalCompressorSetpointTemperatureSchedule();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Compressor Setpoint Temperature Schedule attached.");
    }
    return value.get();
  }

  double WaterHeaterHeatPump_Impl::deadBandTemperatureDifference() const {
    boost::optional<double> value = getDouble(OS_WaterHeater_HeatPumpFields::DeadBandTemperatureDifference,true);
    OS_ASSERT(value);
    return value.get();
  }

  boost::optional<double> WaterHeaterHeatPump_Impl::condenserWaterFlowRate() const {
    return getDouble(OS_WaterHeater_HeatPumpFields::CondenserWaterFlowRate,true);
  }

  bool WaterHeaterHeatPump_Impl::isCondenserWaterFlowRateAutosized() const {
    bool result = false;
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::CondenserWaterFlowRate, true);
    if (value) {
      result = openstudio::istringEqual(value.get(), "autosize");
    }
    return result;
  }

  boost::optional<double> WaterHeaterHeatPump_Impl::evaporatorAirFlowRate() const {
    return getDouble(OS_WaterHeater_HeatPumpFields::EvaporatorAirFlowRate,true);
  }

  bool WaterHeaterHeatPump_Impl::isEvaporatorAirFlowRateAutosized() const {
    bool result = false;
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::EvaporatorAirFlowRate, true);
    if (value) {
      result = openstudio::istringEqual(value.get(), "autosize");
    }
    return result;
  }

  std::string WaterHeaterHeatPump_Impl::inletAirConfiguration() const {
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::InletAirConfiguration,true);
    OS_ASSERT(value);
    return value.get();
  }

  boost::optional<Schedule> WaterHeaterHeatPump_Impl::inletAirTemperatureSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_WaterHeater_HeatPumpFields::InletAirTemperatureSchedule);
  }

  boost::optional<Schedule> WaterHeaterHeatPump_Impl::inletAirHumiditySchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_WaterHeater_HeatPumpFields::InletAirHumiditySchedule);
  }

  HVACComponent WaterHeaterHeatPump_Impl::tank() const {
    auto value = optionalTank();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Tank attached.");
    }
    return value.get();
  }

  ModelObject WaterHeaterHeatPump_Impl::dXCoil() const {
    auto value = optionalDXCoil();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an DXCoil attached.");
    }
    return value.get();
  }

  double WaterHeaterHeatPump_Impl::minimumInletAirTemperatureforCompressorOperation() const {
    boost::optional<double> value = getDouble(OS_WaterHeater_HeatPumpFields::MinimumInletAirTemperatureforCompressorOperation,true);
    OS_ASSERT(value);
    return value.get();
  }

  std::string WaterHeaterHeatPump_Impl::compressorLocation() const {
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::CompressorLocation,true);
    OS_ASSERT(value);
    return value.get();
  }

  boost::optional<Schedule> WaterHeaterHeatPump_Impl::compressorAmbientTemperatureSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_WaterHeater_HeatPumpFields::CompressorAmbientTemperatureSchedule);
  }

  HVACComponent WaterHeaterHeatPump_Impl::fan() const {
    auto value = optionalFan();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Fan attached.");
    }
    return value.get();
  }

  std::string WaterHeaterHeatPump_Impl::fanPlacement() const {
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::FanPlacement,true);
    OS_ASSERT(value);
    return value.get();
  }

  double WaterHeaterHeatPump_Impl::onCycleParasiticElectricLoad() const {
    boost::optional<double> value = getDouble(OS_WaterHeater_HeatPumpFields::OnCycleParasiticElectricLoad,true);
    OS_ASSERT(value);
    return value.get();
  }

  double WaterHeaterHeatPump_Impl::offCycleParasiticElectricLoad() const {
    boost::optional<double> value = getDouble(OS_WaterHeater_HeatPumpFields::OffCycleParasiticElectricLoad,true);
    OS_ASSERT(value);
    return value.get();
  }

  std::string WaterHeaterHeatPump_Impl::parasiticHeatRejectionLocation() const {
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::ParasiticHeatRejectionLocation,true);
    OS_ASSERT(value);
    return value.get();
  }

  Schedule WaterHeaterHeatPump_Impl::inletAirMixerSchedule() const {
    boost::optional<Schedule> value = optionalInletAirMixerSchedule();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Inlet Air Mixer Schedule attached.");
    }
    return value.get();
  }

  std::string WaterHeaterHeatPump_Impl::controlSensorLocationInStratifiedTank() const {
    boost::optional<std::string> value = getString(OS_WaterHeater_HeatPumpFields::ControlSensorLocationInStratifiedTank,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool WaterHeaterHeatPump_Impl::setAvailabilitySchedule(Schedule& schedule) {
    bool result = setSchedule(OS_WaterHeater_HeatPumpFields::AvailabilitySchedule,
                              "WaterHeaterHeatPump",
                              "Availability Schedule",
                              schedule);
    return result;
  }

  void WaterHeaterHeatPump_Impl::resetAvailabilitySchedule() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::AvailabilitySchedule, "");
    OS_ASSERT(result);
  }

  bool WaterHeaterHeatPump_Impl::setCompressorSetpointTemperatureSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_WaterHeater_HeatPumpFields::CompressorSetpointTemperatureSchedule,
                              "WaterHeaterHeatPump",
                              "Compressor Setpoint Temperature Schedule",
                              schedule);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
    bool result = setDouble(OS_WaterHeater_HeatPumpFields::DeadBandTemperatureDifference, deadBandTemperatureDifference);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setCondenserWaterFlowRate(boost::optional<double> condenserWaterFlowRate) {
    bool result(false);
    if (condenserWaterFlowRate) {
      result = setDouble(OS_WaterHeater_HeatPumpFields::CondenserWaterFlowRate, condenserWaterFlowRate.get());
    }
    else {
      resetCondenserWaterFlowRate();
      result = true;
    }
    return result;
  }

  void WaterHeaterHeatPump_Impl::resetCondenserWaterFlowRate() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::CondenserWaterFlowRate, "");
    OS_ASSERT(result);
  }

  void WaterHeaterHeatPump_Impl::autosizeCondenserWaterFlowRate() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::CondenserWaterFlowRate, "autosize");
    OS_ASSERT(result);
  }

  bool WaterHeaterHeatPump_Impl::setEvaporatorAirFlowRate(boost::optional<double> evaporatorAirFlowRate) {
    bool result(false);
    if (evaporatorAirFlowRate) {
      result = setDouble(OS_WaterHeater_HeatPumpFields::EvaporatorAirFlowRate, evaporatorAirFlowRate.get());
    }
    else {
      resetEvaporatorAirFlowRate();
      result = true;
    }
    return result;
  }

  void WaterHeaterHeatPump_Impl::resetEvaporatorAirFlowRate() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::EvaporatorAirFlowRate, "");
    OS_ASSERT(result);
  }

  void WaterHeaterHeatPump_Impl::autosizeEvaporatorAirFlowRate() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::EvaporatorAirFlowRate, "autosize");
    OS_ASSERT(result);
  }

  bool WaterHeaterHeatPump_Impl::setInletAirConfiguration(std::string inletAirConfiguration) {
    bool result = setString(OS_WaterHeater_HeatPumpFields::InletAirConfiguration, inletAirConfiguration);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setInletAirTemperatureSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_WaterHeater_HeatPumpFields::InletAirTemperatureSchedule,
                              "WaterHeaterHeatPump",
                              "Inlet Air Temperature Schedule",
                              schedule);
    return result;
  }

  void WaterHeaterHeatPump_Impl::resetInletAirTemperatureSchedule() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::InletAirTemperatureSchedule, "");
    OS_ASSERT(result);
  }

  bool WaterHeaterHeatPump_Impl::setInletAirHumiditySchedule(Schedule& schedule) {
    bool result = setSchedule(OS_WaterHeater_HeatPumpFields::InletAirHumiditySchedule,
                              "WaterHeaterHeatPump",
                              "Inlet Air Humidity Schedule",
                              schedule);
    return result;
  }

  void WaterHeaterHeatPump_Impl::resetInletAirHumiditySchedule() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::InletAirHumiditySchedule, "");
    OS_ASSERT(result);
  }

  bool WaterHeaterHeatPump_Impl::setTank(const HVACComponent& waterHeater) {
    bool result = setPointer(OS_WaterHeater_HeatPumpFields::Tank, waterHeater.handle());
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoils) {
    bool result = setPointer(OS_WaterHeater_HeatPumpFields::DXCoil, heatPumpWaterHeaterDXCoils.handle());
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setMinimumInletAirTemperatureforCompressorOperation(double minimumInletAirTemperatureforCompressorOperation) {
    bool result = setDouble(OS_WaterHeater_HeatPumpFields::MinimumInletAirTemperatureforCompressorOperation, minimumInletAirTemperatureforCompressorOperation);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setCompressorLocation(std::string compressorLocation) {
    bool result = setString(OS_WaterHeater_HeatPumpFields::CompressorLocation, compressorLocation);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setCompressorAmbientTemperatureSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_WaterHeater_HeatPumpFields::CompressorAmbientTemperatureSchedule,
                              "WaterHeaterHeatPump",
                              "Compressor Ambient Temperature Schedule",
                              schedule);
    return result;
  }

  void WaterHeaterHeatPump_Impl::resetCompressorAmbientTemperatureSchedule() {
    bool result = setString(OS_WaterHeater_HeatPumpFields::CompressorAmbientTemperatureSchedule, "");
    OS_ASSERT(result);
  }

  bool WaterHeaterHeatPump_Impl::setFan(const HVACComponent& fansOnOff) {
    bool result = setPointer(OS_WaterHeater_HeatPumpFields::Fan, fansOnOff.handle());
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setFanPlacement(std::string fanPlacement) {
    bool result = setString(OS_WaterHeater_HeatPumpFields::FanPlacement, fanPlacement);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
    bool result = setDouble(OS_WaterHeater_HeatPumpFields::OnCycleParasiticElectricLoad, onCycleParasiticElectricLoad);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
    bool result = setDouble(OS_WaterHeater_HeatPumpFields::OffCycleParasiticElectricLoad, offCycleParasiticElectricLoad);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setParasiticHeatRejectionLocation(std::string parasiticHeatRejectionLocation) {
    bool result = setString(OS_WaterHeater_HeatPumpFields::ParasiticHeatRejectionLocation, parasiticHeatRejectionLocation);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setInletAirMixerSchedule(Schedule& schedule) {
    bool result = setSchedule(OS_WaterHeater_HeatPumpFields::InletAirMixerSchedule,
                              "WaterHeaterHeatPump",
                              "Inlet Air Mixer Schedule",
                              schedule);
    return result;
  }

  bool WaterHeaterHeatPump_Impl::setControlSensorLocationInStratifiedTank(std::string controlSensorLocationInStratifiedTank) {
    bool result = setString(OS_WaterHeater_HeatPumpFields::ControlSensorLocationInStratifiedTank, controlSensorLocationInStratifiedTank);
    return result;
  }

  boost::optional<Schedule> WaterHeaterHeatPump_Impl::optionalCompressorSetpointTemperatureSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_WaterHeater_HeatPumpFields::CompressorSetpointTemperatureSchedule);
  }

  boost::optional<HVACComponent> WaterHeaterHeatPump_Impl::optionalTank() const {
    return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(OS_WaterHeater_HeatPumpFields::Tank);
  }

  boost::optional<ModelObject> WaterHeaterHeatPump_Impl::optionalDXCoil() const {
    return getObject<ModelObject>().getModelObjectTarget<ModelObject>(OS_WaterHeater_HeatPumpFields::DXCoil);
  }

  boost::optional<HVACComponent> WaterHeaterHeatPump_Impl::optionalFan() const {
    return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(OS_WaterHeater_HeatPumpFields::Fan);
  }

  boost::optional<Schedule> WaterHeaterHeatPump_Impl::optionalInletAirMixerSchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_WaterHeater_HeatPumpFields::InletAirMixerSchedule);
  }

  unsigned WaterHeaterHeatPump_Impl::inletPort() const {
    return OS_WaterHeater_HeatPumpFields::AirInletNode;
  }

  unsigned WaterHeaterHeatPump_Impl::outletPort() const {
    return OS_WaterHeater_HeatPumpFields::AirOutletNode;
  }

  ModelObject WaterHeaterHeatPump_Impl::clone(Model model) const
  {
    auto newWaterHeater = ZoneHVACComponent_Impl::clone(model).cast<WaterHeaterHeatPump>();

    {
      auto mo = tank().clone(model).cast<HVACComponent>();
      newWaterHeater.setTank(mo);
    }

    {
      auto mo = dXCoil().clone(model).cast<ModelObject>();
      newWaterHeater.setDXCoil(mo);
    }

    {
      auto mo = fan().clone(model).cast<HVACComponent>();
      newWaterHeater.setFan(mo);
    }

    return newWaterHeater;
  }

  std::vector<ModelObject> WaterHeaterHeatPump_Impl::children() const
  {
    std::vector<ModelObject> result;

    result.push_back(tank());
    result.push_back(dXCoil());
    result.push_back(fan());

    return result;
  }

} // detail

WaterHeaterHeatPump::WaterHeaterHeatPump(const Model& model)
  : ZoneHVACComponent(WaterHeaterHeatPump::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::WaterHeaterHeatPump_Impl>());

  CoilWaterHeatingAirToWaterHeatPump coil(model);
  setDXCoil(coil);

  WaterHeaterMixed waterHeater(model);
  setTank(waterHeater);

  FanOnOff fan(model);
  setFan(fan);

  {
    ScheduleRuleset schedule(model);
    schedule.defaultDaySchedule().addValue(Time(0,24,0,0),60.0);
    setCompressorSetpointTemperatureSchedule(schedule);
  }

  {
    ScheduleRuleset schedule(model);
    schedule.defaultDaySchedule().addValue(Time(0,24,0,0),0.2);
    setInletAirMixerSchedule(schedule);
  }

  setDeadBandTemperatureDifference(5.0);
  autosizeCondenserWaterFlowRate();
  autosizeEvaporatorAirFlowRate();
  setInletAirConfiguration("ZoneAirOnly");
  setMinimumInletAirTemperatureforCompressorOperation(10.0);
  setCompressorLocation("Zone");
  setFanPlacement("DrawThrough");
  setOnCycleParasiticElectricLoad(0.0);
  setOffCycleParasiticElectricLoad(0.0);
  setParasiticHeatRejectionLocation("Outdoors");
  setControlSensorLocationInStratifiedTank("Heater1");

}

IddObjectType WaterHeaterHeatPump::iddObjectType() {
  return IddObjectType(IddObjectType::OS_WaterHeater_HeatPump);
}

std::vector<std::string> WaterHeaterHeatPump::inletAirConfigurationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_WaterHeater_HeatPumpFields::InletAirConfiguration);
}

std::vector<std::string> WaterHeaterHeatPump::compressorLocationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_WaterHeater_HeatPumpFields::CompressorLocation);
}

std::vector<std::string> WaterHeaterHeatPump::fanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_WaterHeater_HeatPumpFields::FanPlacement);
}

std::vector<std::string> WaterHeaterHeatPump::parasiticHeatRejectionLocationValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_WaterHeater_HeatPumpFields::ParasiticHeatRejectionLocation);
}

std::vector<std::string> WaterHeaterHeatPump::controlSensorLocationInStratifiedTankValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_WaterHeater_HeatPumpFields::ControlSensorLocationInStratifiedTank);
}

boost::optional<Schedule> WaterHeaterHeatPump::availabilitySchedule() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->availabilitySchedule();
}

Schedule WaterHeaterHeatPump::compressorSetpointTemperatureSchedule() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->compressorSetpointTemperatureSchedule();
}

double WaterHeaterHeatPump::deadBandTemperatureDifference() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->deadBandTemperatureDifference();
}

boost::optional<double> WaterHeaterHeatPump::condenserWaterFlowRate() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->condenserWaterFlowRate();
}

bool WaterHeaterHeatPump::isCondenserWaterFlowRateAutosized() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->isCondenserWaterFlowRateAutosized();
}

boost::optional<double> WaterHeaterHeatPump::evaporatorAirFlowRate() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->evaporatorAirFlowRate();
}

bool WaterHeaterHeatPump::isEvaporatorAirFlowRateAutosized() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->isEvaporatorAirFlowRateAutosized();
}

std::string WaterHeaterHeatPump::inletAirConfiguration() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirConfiguration();
}

boost::optional<Schedule> WaterHeaterHeatPump::inletAirTemperatureSchedule() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirTemperatureSchedule();
}

boost::optional<Schedule> WaterHeaterHeatPump::inletAirHumiditySchedule() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirHumiditySchedule();
}

HVACComponent WaterHeaterHeatPump::tank() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->tank();
}

ModelObject WaterHeaterHeatPump::dXCoil() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->dXCoil();
}

double WaterHeaterHeatPump::minimumInletAirTemperatureforCompressorOperation() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->minimumInletAirTemperatureforCompressorOperation();
}

std::string WaterHeaterHeatPump::compressorLocation() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->compressorLocation();
}

boost::optional<Schedule> WaterHeaterHeatPump::compressorAmbientTemperatureSchedule() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->compressorAmbientTemperatureSchedule();
}

HVACComponent WaterHeaterHeatPump::fan() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->fan();
}

std::string WaterHeaterHeatPump::fanPlacement() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->fanPlacement();
}

double WaterHeaterHeatPump::onCycleParasiticElectricLoad() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->onCycleParasiticElectricLoad();
}

double WaterHeaterHeatPump::offCycleParasiticElectricLoad() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->offCycleParasiticElectricLoad();
}

std::string WaterHeaterHeatPump::parasiticHeatRejectionLocation() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->parasiticHeatRejectionLocation();
}

Schedule WaterHeaterHeatPump::inletAirMixerSchedule() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->inletAirMixerSchedule();
}

std::string WaterHeaterHeatPump::controlSensorLocationInStratifiedTank() const {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->controlSensorLocationInStratifiedTank();
}

bool WaterHeaterHeatPump::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setAvailabilitySchedule(schedule);
}

void WaterHeaterHeatPump::resetAvailabilitySchedule() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->resetAvailabilitySchedule();
}

bool WaterHeaterHeatPump::setCompressorSetpointTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCompressorSetpointTemperatureSchedule(schedule);
}

bool WaterHeaterHeatPump::setDeadBandTemperatureDifference(double deadBandTemperatureDifference) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setDeadBandTemperatureDifference(deadBandTemperatureDifference);
}

bool WaterHeaterHeatPump::setCondenserWaterFlowRate(double condenserWaterFlowRate) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCondenserWaterFlowRate(condenserWaterFlowRate);
}

void WaterHeaterHeatPump::resetCondenserWaterFlowRate() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->resetCondenserWaterFlowRate();
}

void WaterHeaterHeatPump::autosizeCondenserWaterFlowRate() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->autosizeCondenserWaterFlowRate();
}

bool WaterHeaterHeatPump::setEvaporatorAirFlowRate(double evaporatorAirFlowRate) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setEvaporatorAirFlowRate(evaporatorAirFlowRate);
}

void WaterHeaterHeatPump::resetEvaporatorAirFlowRate() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->resetEvaporatorAirFlowRate();
}

void WaterHeaterHeatPump::autosizeEvaporatorAirFlowRate() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->autosizeEvaporatorAirFlowRate();
}

bool WaterHeaterHeatPump::setInletAirConfiguration(std::string inletAirConfiguration) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirConfiguration(inletAirConfiguration);
}

bool WaterHeaterHeatPump::setInletAirTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirTemperatureSchedule(schedule);
}

void WaterHeaterHeatPump::resetInletAirTemperatureSchedule() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->resetInletAirTemperatureSchedule();
}

bool WaterHeaterHeatPump::setInletAirHumiditySchedule(Schedule& schedule) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirHumiditySchedule(schedule);
}

void WaterHeaterHeatPump::resetInletAirHumiditySchedule() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->resetInletAirHumiditySchedule();
}

bool WaterHeaterHeatPump::setTank(const HVACComponent& waterHeater) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setTank(waterHeater);
}

bool WaterHeaterHeatPump::setDXCoil(const ModelObject& coil) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setDXCoil(coil);
}

bool WaterHeaterHeatPump::setMinimumInletAirTemperatureforCompressorOperation(double minimumInletAirTemperatureforCompressorOperation) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setMinimumInletAirTemperatureforCompressorOperation(minimumInletAirTemperatureforCompressorOperation);
}

bool WaterHeaterHeatPump::setCompressorLocation(std::string compressorLocation) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCompressorLocation(compressorLocation);
}

bool WaterHeaterHeatPump::setCompressorAmbientTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setCompressorAmbientTemperatureSchedule(schedule);
}

void WaterHeaterHeatPump::resetCompressorAmbientTemperatureSchedule() {
  getImpl<detail::WaterHeaterHeatPump_Impl>()->resetCompressorAmbientTemperatureSchedule();
}

bool WaterHeaterHeatPump::setFan(const HVACComponent& fan) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setFan(fan);
}

bool WaterHeaterHeatPump::setFanPlacement(std::string fanPlacement) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setFanPlacement(fanPlacement);
}

bool WaterHeaterHeatPump::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setOnCycleParasiticElectricLoad(onCycleParasiticElectricLoad);
}

bool WaterHeaterHeatPump::setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setOffCycleParasiticElectricLoad(offCycleParasiticElectricLoad);
}

bool WaterHeaterHeatPump::setParasiticHeatRejectionLocation(std::string parasiticHeatRejectionLocation) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setParasiticHeatRejectionLocation(parasiticHeatRejectionLocation);
}

bool WaterHeaterHeatPump::setInletAirMixerSchedule(Schedule& schedule) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setInletAirMixerSchedule(schedule);
}

bool WaterHeaterHeatPump::setControlSensorLocationInStratifiedTank(std::string controlSensorLocationInStratifiedTank) {
  return getImpl<detail::WaterHeaterHeatPump_Impl>()->setControlSensorLocationInStratifiedTank(controlSensorLocationInStratifiedTank);
}

/// @cond
WaterHeaterHeatPump::WaterHeaterHeatPump(std::shared_ptr<detail::WaterHeaterHeatPump_Impl> impl)
  : ZoneHVACComponent(impl)
{}
/// @endcond

} // model
} // openstudio

