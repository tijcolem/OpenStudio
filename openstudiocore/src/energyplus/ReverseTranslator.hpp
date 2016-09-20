/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#ifndef ENERGYPLUS_REVERSETRANSLATOR_HPP
#define ENERGYPLUS_REVERSETRANSLATOR_HPP

#include "EnergyPlusAPI.hpp"
#include "../model/Model.hpp"
#include "../utilities/core/Logger.hpp"
#include "../utilities/core/StringStreamLogSink.hpp"

namespace openstudio {

class ProgressBar;

namespace energyplus {

class ENERGYPLUS_API ReverseTranslator {
 public:

  ReverseTranslator();

  boost::optional<model::Model> loadModel(const openstudio::path& path, ProgressBar* progressBar=nullptr);

  model::Model translateWorkspace(const Workspace & workspace, ProgressBar* progressBar=nullptr );

  /** Get warning messages generated by the last translation. */
  std::vector<LogMessage> warnings() const;

  /** Get error messages generated by the last translation. */
  std::vector<LogMessage> errors() const;

  /** Get IdfObjects that were passed over by the last translation. */
  std::vector<IdfObject> untranslatedIdfObjects() const;

 private:

  REGISTER_LOGGER("openstudio.energyplus.ReverseTranslator");


  /** Translates the given Workspace to a Model.
   *
   *  This method carries out its work by explicitly translating the highest level objects in 
   *  the Workspace by calling translateAndMapWorkspaceObject().  The translateAndMapWorkspaceObject method in turn calls a type
   *  specific function to translate the given object.  Each type specific function is responsible for translating
   *  not only the direct workspace object passed into it, but also related objects under its purview.  Related objects
   *  are often identified by an object list reference pointing to them, but this rule is not absolute.  For example,
   *  AirLoopHVAC is connected to other components via node connections and the translate function for AirLoopHVAC
   *  is responsbile for translating the components associated with the loop.  The method translateAndMapWorkspaceObject()
   *  uses an internal map to determine if an object has already been translated, therefore there is no
   *  concern of translating an object twice, provided that workspace objects are always translated using the 
   *  translateAndMapWorkspaceObject() interface as opposed to the type specific translators.
   */
  boost::optional<model::ModelObject> translateAndMapWorkspaceObject(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateAirLoopHVAC(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateAirLoopHVACOutdoorAirSystem(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateAirTerminalSingleDuctConstantVolumeReheat(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateAirTerminalSingleDuctUncontrolled(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateAirTerminalSingleDuctVAVNoReheat(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateAirTerminalSingleDuctVAVReheat(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateBuilding(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateBuildingSurfaceDetailed(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateControllerOutdoorAir(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateCoilHeatingGas(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateCoilCoolingDXSingleSpeed( const WorkspaceObject& orkspaceObject);

  boost::optional<model::ModelObject> translateCoilSystemCoolingDX(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateConstruction(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateConvergenceLimits(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateCurveBicubic(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveBiquadratic(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveCubic(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveDoubleExponentialDecay(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveExponent(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveExponentialDecay(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveExponentialSkewNormal(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveFanPressureRise(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveFunctionalPressureDrop(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveLinear(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveQuadratic(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveQuadraticLinear(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveQuartic(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveRectangularHyperbola1(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveRectangularHyperbola2(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveSigmoid(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateCurveTriquadratic(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateDaylightingControls( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateDesignSpecificationOutdoorAir( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateElectricEquipment(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateElectricLoadCenterStorageSimple(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateEnergyManagementSystemSensor(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateElectricLoadCenterStorageConverter(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateEvaporativeCoolerDirectResearchSpecial(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateEvaporativeFluidCoolerSingleSpeed(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateExteriorLights(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateFanConstantVolume(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateFenestrationSurfaceDetailed(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateGasEquipment(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateGeneratorMicroTurbine(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateGroundHeatExchangerVertical(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateHeatBalanceAlgorithm(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateHotWaterEquipment(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateInternalMass(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateLights(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateMaterial(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateMaterialAirGap(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateMaterialNoMass(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateMeterCustom(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateMeterCustomDecrement(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateOtherEquipment(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateOutputIlluminanceMap( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateOutputMeter( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateOutputMeterCumulative( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateOutputMeterCumulativeMeterFileOnly( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateOutputMeterMeterFileOnly( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateOutputVariable( const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translatePeople(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSizingPeriodDesignDay(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateRefrigerationCase(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateRefrigerationCompressor(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateRunPeriod(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateRunPeriodControlDaylightSavingTime(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateRunPeriodControlSpecialDays(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleCompact(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleConstant(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleDayHourly(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleDayInterval(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleTypeLimits(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleWeekDaily(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateScheduleYear(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSetpointManagerMixedAir(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSetpointManagerScheduled(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSetpointManagerSingleZoneReheat(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateShadingBuildingDetailed(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateShadingSiteDetailed(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateShadingZoneDetailed(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateShadowCalculation(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateSimulationControl(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSiteLocation(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSiteGroundReflectance(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSiteGroundTemperatureBuildingSurface(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSiteWaterMainsTemperature(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSizingParameters(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSizingSystem(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSizingZone(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSteamEquipment(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateSurfaceConvectionAlgorithmInside(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateSurfaceConvectionAlgorithmOutside(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateThermostatSetpointDualSetpoint(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateTimestep(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateVersion(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateWindowMaterialGas(const WorkspaceObject& workspaceObject);

  boost::optional<model::ModelObject> translateWindowMaterialGlazing(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateWindowMaterialSimpleGlazingSystem(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateWindowPropertyFrameAndDivider(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZone(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneAirHeatBalanceAlgorithm(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneAirMassFlowConservation(const WorkspaceObject & workspaceObject);
  
  boost::optional<model::ModelObject> translateZoneCrossMixing(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneHVACEquipmentList(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneHVACIdealLoadsAirSystem(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneInfiltrationDesignFlowRate(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneInfiltrationEffectiveLeakageArea(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneList(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneMixing(const WorkspaceObject & workspaceObject);

  boost::optional<model::ModelObject> translateZoneVentilationDesignFlowRate(const WorkspaceObject & workspaceObject);

  std::map<openstudio::Handle,model::ModelObject> m_workspaceToModelMap;

  Workspace m_workspace;

  model::Model m_model;

  std::vector<IdfObject> m_untranslatedIdfObjects;

  StringStreamLogSink m_logSink;

  ProgressBar* m_progressBar;
};


ENERGYPLUS_API boost::optional<openstudio::model::Model> loadAndTranslateIdf(const openstudio::path& path);

} // energyplus

} // openstudio

#endif // ENERGYPLUS_REVERSETRANSLATOR_HPP

