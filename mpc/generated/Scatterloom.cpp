/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)
#include "StatusBridge.h" // SCATTERLOOM_STATUS_BRIDGE

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{
    deallocateSignals();
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->beatstosamps_tilde_01_perform(this->beatstosamps_tilde_01_beattime, this->signals[0], n);

    this->gen_01_perform(
        in1,
        in2,
        this->gen_01_in3,
        this->signals[0],
        this->gen_01_in5,
        this->gen_01_sensitivity,
        this->gen_01_autoSensitivity,
        this->gen_01_captureOn,
        this->gen_01_grain,
        this->gen_01_attack,
        this->gen_01_grainCount,
        this->gen_01_steps,
        this->gen_01_pulses,
        this->gen_01_rotation,
        this->gen_01_feedback,
        this->gen_01_mixAmount,
        this->gen_01_grainFeedback,
        this->gen_01_reverseProbability,
        this->gen_01_clearPool,
        this->gen_01_division,
        this->gen_01_rotationInterval,
        this->gen_01_grainPan0,
        this->gen_01_grainPan1,
        this->gen_01_grainPan2,
        this->gen_01_grainPan3,
        this->gen_01_grainPan4,
        this->gen_01_grainPan5,
        this->gen_01_grainPan6,
        this->gen_01_grainPan7,
        this->gen_01_grainPan8,
        this->gen_01_grainSelectionMode,
        this->gen_01_loopDivision,
        this->gen_01_timingOffset,
        this->gen_01_removeGrain,
        this->gen_01_auditionGrain,
        this->gen_01_reorderFrom,
        this->gen_01_reorderTo,
        this->gen_01_reorderCommit,
        this->gen_01_markovWeight0,
        this->gen_01_markovWeight1,
        this->gen_01_markovWeight2,
        this->gen_01_markovWeight3,
        this->gen_01_markovWeight4,
        this->gen_01_markovWeight5,
        this->gen_01_markovWeight6,
        this->gen_01_markovWeight7,
        this->gen_01_markovWeight8,
        this->gen_01_markovEditRow,
        this->gen_01_markovCommit,
        out1,
        out2,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        this->dummyBuffer,
        n
    );

    ::scatterloomPublishStatus(this->scatterloomEffectiveRotation, this->scatterloomEffectiveSensitivity,
                               this->scatterloomPoolCount, this->scatterloomClearActive,
                               this->scatterloomCurrentStep, this->scatterloomTransportRunning);

    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 1; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->gen_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->markovMatrixB_70);
        break;
        }
    case 1:
        {
        return addressOf(this->markovMatrixA_69);
        break;
        }
    case 2:
        {
        return addressOf(this->trimEnds_68);
        break;
        }
    case 3:
        {
        return addressOf(this->trimStarts_67);
        break;
        }
    case 4:
        {
        return addressOf(this->grainLevels_66);
        break;
        }
    case 5:
        {
        return addressOf(this->captureActive_65);
        break;
        }
    case 6:
        {
        return addressOf(this->capturePositions_64);
        break;
        }
    case 7:
        {
        return addressOf(this->grainQueue_63);
        break;
        }
    case 8:
        {
        return addressOf(this->poolR_62);
        break;
        }
    case 9:
        {
        return addressOf(this->poolL_61);
        break;
        }
    case 10:
        {
        return addressOf(this->gen_01_feedbackR_75_bufferobj);
        break;
        }
    case 11:
        {
        return addressOf(this->gen_01_feedbackL_74_bufferobj);
        break;
        }
    case 12:
        {
        return addressOf(this->gen_01_triggerDelay_73_bufferobj);
        break;
        }
    case 13:
        {
        return addressOf(this->gen_01_preR_72_bufferobj);
        break;
        }
    case 14:
        {
        return addressOf(this->gen_01_preL_71_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 15;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (index == 0) {
        this->gen_01_markovMatrixB_70 = reInitDataView(this->gen_01_markovMatrixB_70, this->markovMatrixB_70);
    }

    if (index == 1) {
        this->gen_01_markovMatrixA_69 = reInitDataView(this->gen_01_markovMatrixA_69, this->markovMatrixA_69);
    }

    if (index == 2) {
        this->gen_01_trimEnds_68 = reInitDataView(this->gen_01_trimEnds_68, this->trimEnds_68);
    }

    if (index == 3) {
        this->gen_01_trimStarts_67 = reInitDataView(this->gen_01_trimStarts_67, this->trimStarts_67);
    }

    if (index == 4) {
        this->gen_01_grainLevels_66 = reInitDataView(this->gen_01_grainLevels_66, this->grainLevels_66);
    }

    if (index == 5) {
        this->gen_01_captureActive_65 = reInitDataView(this->gen_01_captureActive_65, this->captureActive_65);
    }

    if (index == 6) {
        this->gen_01_capturePositions_64 = reInitDataView(this->gen_01_capturePositions_64, this->capturePositions_64);
    }

    if (index == 7) {
        this->gen_01_grainQueue_63 = reInitDataView(this->gen_01_grainQueue_63, this->grainQueue_63);
    }

    if (index == 8) {
        this->gen_01_poolR_62 = reInitDataView(this->gen_01_poolR_62, this->poolR_62);
    }

    if (index == 9) {
        this->gen_01_poolL_61 = reInitDataView(this->gen_01_poolL_61, this->poolL_61);
    }

    if (index == 10) {
        this->gen_01_feedbackR_75_buffer = reInitDataView(this->gen_01_feedbackR_75_buffer, this->gen_01_feedbackR_75_bufferobj);
    }

    if (index == 11) {
        this->gen_01_feedbackL_74_buffer = reInitDataView(this->gen_01_feedbackL_74_buffer, this->gen_01_feedbackL_74_bufferobj);
    }

    if (index == 12) {
        this->gen_01_triggerDelay_73_buffer = reInitDataView(
            this->gen_01_triggerDelay_73_buffer,
            this->gen_01_triggerDelay_73_bufferobj
        );
    }

    if (index == 13) {
        this->gen_01_preR_72_buffer = reInitDataView(this->gen_01_preR_72_buffer, this->gen_01_preR_72_bufferobj);
    }

    if (index == 14) {
        this->gen_01_preL_71_buffer = reInitDataView(this->gen_01_preL_71_buffer, this->gen_01_preL_71_bufferobj);
    }
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);

    this->markovMatrixB_70 = initDataRef(
        this->markovMatrixB_70,
        this->dataRefStrings->name0,
        true,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->markovMatrixA_69 = initDataRef(
        this->markovMatrixA_69,
        this->dataRefStrings->name1,
        true,
        this->dataRefStrings->file1,
        this->dataRefStrings->tag1
    );

    this->trimEnds_68 = initDataRef(
        this->trimEnds_68,
        this->dataRefStrings->name2,
        true,
        this->dataRefStrings->file2,
        this->dataRefStrings->tag2
    );

    this->trimStarts_67 = initDataRef(
        this->trimStarts_67,
        this->dataRefStrings->name3,
        true,
        this->dataRefStrings->file3,
        this->dataRefStrings->tag3
    );

    this->grainLevels_66 = initDataRef(
        this->grainLevels_66,
        this->dataRefStrings->name4,
        true,
        this->dataRefStrings->file4,
        this->dataRefStrings->tag4
    );

    this->captureActive_65 = initDataRef(
        this->captureActive_65,
        this->dataRefStrings->name5,
        true,
        this->dataRefStrings->file5,
        this->dataRefStrings->tag5
    );

    this->capturePositions_64 = initDataRef(
        this->capturePositions_64,
        this->dataRefStrings->name6,
        true,
        this->dataRefStrings->file6,
        this->dataRefStrings->tag6
    );

    this->grainQueue_63 = initDataRef(
        this->grainQueue_63,
        this->dataRefStrings->name7,
        true,
        this->dataRefStrings->file7,
        this->dataRefStrings->tag7
    );

    this->poolR_62 = initDataRef(
        this->poolR_62,
        this->dataRefStrings->name8,
        true,
        this->dataRefStrings->file8,
        this->dataRefStrings->tag8
    );

    this->poolL_61 = initDataRef(
        this->poolL_61,
        this->dataRefStrings->name9,
        true,
        this->dataRefStrings->file9,
        this->dataRefStrings->tag9
    );

    this->gen_01_feedbackR_75_bufferobj = initDataRef(
        this->gen_01_feedbackR_75_bufferobj,
        this->dataRefStrings->name10,
        true,
        this->dataRefStrings->file10,
        this->dataRefStrings->tag10
    );

    this->gen_01_feedbackL_74_bufferobj = initDataRef(
        this->gen_01_feedbackL_74_bufferobj,
        this->dataRefStrings->name11,
        true,
        this->dataRefStrings->file11,
        this->dataRefStrings->tag11
    );

    this->gen_01_triggerDelay_73_bufferobj = initDataRef(
        this->gen_01_triggerDelay_73_bufferobj,
        this->dataRefStrings->name12,
        true,
        this->dataRefStrings->file12,
        this->dataRefStrings->tag12
    );

    this->gen_01_preR_72_bufferobj = initDataRef(
        this->gen_01_preR_72_bufferobj,
        this->dataRefStrings->name13,
        true,
        this->dataRefStrings->file13,
        this->dataRefStrings->tag13
    );

    this->gen_01_preL_71_bufferobj = initDataRef(
        this->gen_01_preL_71_bufferobj,
        this->dataRefStrings->name14,
        true,
        this->dataRefStrings->file14,
        this->dataRefStrings->tag14
    );

    this->assign_defaults();
    this->applyState();
    this->markovMatrixB_70->setIndex(0);
    this->gen_01_markovMatrixB_70 = new SampleBuffer(this->markovMatrixB_70);
    this->markovMatrixA_69->setIndex(1);
    this->gen_01_markovMatrixA_69 = new SampleBuffer(this->markovMatrixA_69);
    this->trimEnds_68->setIndex(2);
    this->gen_01_trimEnds_68 = new SampleBuffer(this->trimEnds_68);
    this->trimStarts_67->setIndex(3);
    this->gen_01_trimStarts_67 = new SampleBuffer(this->trimStarts_67);
    this->grainLevels_66->setIndex(4);
    this->gen_01_grainLevels_66 = new SampleBuffer(this->grainLevels_66);
    this->captureActive_65->setIndex(5);
    this->gen_01_captureActive_65 = new SampleBuffer(this->captureActive_65);
    this->capturePositions_64->setIndex(6);
    this->gen_01_capturePositions_64 = new SampleBuffer(this->capturePositions_64);
    this->grainQueue_63->setIndex(7);
    this->gen_01_grainQueue_63 = new SampleBuffer(this->grainQueue_63);
    this->poolR_62->setIndex(8);
    this->gen_01_poolR_62 = new SampleBuffer(this->poolR_62);
    this->poolL_61->setIndex(9);
    this->gen_01_poolL_61 = new SampleBuffer(this->poolL_61);
    this->gen_01_feedbackR_75_bufferobj->setIndex(10);
    this->gen_01_feedbackR_75_buffer = new Float64Buffer(this->gen_01_feedbackR_75_bufferobj);
    this->gen_01_feedbackL_74_bufferobj->setIndex(11);
    this->gen_01_feedbackL_74_buffer = new Float64Buffer(this->gen_01_feedbackL_74_bufferobj);
    this->gen_01_triggerDelay_73_bufferobj->setIndex(12);
    this->gen_01_triggerDelay_73_buffer = new Float64Buffer(this->gen_01_triggerDelay_73_bufferobj);
    this->gen_01_preR_72_bufferobj->setIndex(13);
    this->gen_01_preR_72_buffer = new Float64Buffer(this->gen_01_preR_72_bufferobj);
    this->gen_01_preL_71_bufferobj->setIndex(14);
    this->gen_01_preL_71_buffer = new Float64Buffer(this->gen_01_preL_71_bufferobj);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->transport_01_onTempoChanged(tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->transport_01_onTransportChanged(state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false))
        {}
}

void processTimeSignatureEvent(MillisecondTime time, Int numerator, Int denominator) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->transport_01_onTimeSignatureChanged(numerator, denominator);
    }
}

void processBBUEvent(MillisecondTime time, number bars, number beats, number units) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBBU(this->_currentTime, bars, beats, units, false))
        {}
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->gen_01_param_ScatterloomDSP_sensitivity_getPresetValue(getSubState(preset, "ScatterloomDSP/sensitivity"));
    this->gen_01_param_ScatterloomDSP_autoSensitivity_getPresetValue(getSubState(preset, "ScatterloomDSP/autoSensitivity"));
    this->gen_01_param_ScatterloomDSP_captureOn_getPresetValue(getSubState(preset, "ScatterloomDSP/captureOn"));
    this->gen_01_param_ScatterloomDSP_grain_getPresetValue(getSubState(preset, "ScatterloomDSP/grain"));
    this->gen_01_param_ScatterloomDSP_attack_getPresetValue(getSubState(preset, "ScatterloomDSP/attack"));
    this->gen_01_param_ScatterloomDSP_grainCount_getPresetValue(getSubState(preset, "ScatterloomDSP/grainCount"));
    this->gen_01_param_ScatterloomDSP_steps_getPresetValue(getSubState(preset, "ScatterloomDSP/steps"));
    this->gen_01_param_ScatterloomDSP_pulses_getPresetValue(getSubState(preset, "ScatterloomDSP/pulses"));
    this->gen_01_param_ScatterloomDSP_rotation_getPresetValue(getSubState(preset, "ScatterloomDSP/rotation"));
    this->gen_01_param_ScatterloomDSP_feedback_getPresetValue(getSubState(preset, "ScatterloomDSP/feedback"));
    this->gen_01_param_ScatterloomDSP_mixAmount_getPresetValue(getSubState(preset, "ScatterloomDSP/mixAmount"));
    this->gen_01_param_ScatterloomDSP_grainFeedback_getPresetValue(getSubState(preset, "ScatterloomDSP/grainFeedback"));
    this->gen_01_param_ScatterloomDSP_reverseProbability_getPresetValue(getSubState(preset, "ScatterloomDSP/reverseProbability"));
    this->gen_01_param_ScatterloomDSP_clearPool_getPresetValue(getSubState(preset, "ScatterloomDSP/clearPool"));
    this->gen_01_param_ScatterloomDSP_division_getPresetValue(getSubState(preset, "ScatterloomDSP/division"));
    this->gen_01_param_ScatterloomDSP_rotationInterval_getPresetValue(getSubState(preset, "ScatterloomDSP/rotationInterval"));
    this->gen_01_param_ScatterloomDSP_grainPan0_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan0"));
    this->gen_01_param_ScatterloomDSP_grainPan1_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan1"));
    this->gen_01_param_ScatterloomDSP_grainPan2_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan2"));
    this->gen_01_param_ScatterloomDSP_grainPan3_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan3"));
    this->gen_01_param_ScatterloomDSP_grainPan4_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan4"));
    this->gen_01_param_ScatterloomDSP_grainPan5_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan5"));
    this->gen_01_param_ScatterloomDSP_grainPan6_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan6"));
    this->gen_01_param_ScatterloomDSP_grainPan7_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan7"));
    this->gen_01_param_ScatterloomDSP_grainPan8_getPresetValue(getSubState(preset, "ScatterloomDSP/grainPan8"));
    this->gen_01_param_ScatterloomDSP_grainSelectionMode_getPresetValue(getSubState(preset, "ScatterloomDSP/grainSelectionMode"));
    this->gen_01_param_ScatterloomDSP_loopDivision_getPresetValue(getSubState(preset, "ScatterloomDSP/loopDivision"));
    this->gen_01_param_ScatterloomDSP_timingOffset_getPresetValue(getSubState(preset, "ScatterloomDSP/timingOffset"));
    this->gen_01_param_ScatterloomDSP_removeGrain_getPresetValue(getSubState(preset, "ScatterloomDSP/removeGrain"));
    this->gen_01_param_ScatterloomDSP_auditionGrain_getPresetValue(getSubState(preset, "ScatterloomDSP/auditionGrain"));
    this->gen_01_param_ScatterloomDSP_reorderFrom_getPresetValue(getSubState(preset, "ScatterloomDSP/reorderFrom"));
    this->gen_01_param_ScatterloomDSP_reorderTo_getPresetValue(getSubState(preset, "ScatterloomDSP/reorderTo"));
    this->gen_01_param_ScatterloomDSP_reorderCommit_getPresetValue(getSubState(preset, "ScatterloomDSP/reorderCommit"));
    this->gen_01_param_ScatterloomDSP_markovWeight0_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight0"));
    this->gen_01_param_ScatterloomDSP_markovWeight1_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight1"));
    this->gen_01_param_ScatterloomDSP_markovWeight2_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight2"));
    this->gen_01_param_ScatterloomDSP_markovWeight3_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight3"));
    this->gen_01_param_ScatterloomDSP_markovWeight4_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight4"));
    this->gen_01_param_ScatterloomDSP_markovWeight5_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight5"));
    this->gen_01_param_ScatterloomDSP_markovWeight6_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight6"));
    this->gen_01_param_ScatterloomDSP_markovWeight7_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight7"));
    this->gen_01_param_ScatterloomDSP_markovWeight8_getPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight8"));
    this->gen_01_param_ScatterloomDSP_markovEditRow_getPresetValue(getSubState(preset, "ScatterloomDSP/markovEditRow"));
    this->gen_01_param_ScatterloomDSP_markovCommit_getPresetValue(getSubState(preset, "ScatterloomDSP/markovCommit"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->gen_01_param_ScatterloomDSP_sensitivity_setPresetValue(getSubState(preset, "ScatterloomDSP/sensitivity"));
    this->gen_01_param_ScatterloomDSP_autoSensitivity_setPresetValue(getSubState(preset, "ScatterloomDSP/autoSensitivity"));
    this->gen_01_param_ScatterloomDSP_captureOn_setPresetValue(getSubState(preset, "ScatterloomDSP/captureOn"));
    this->gen_01_param_ScatterloomDSP_grain_setPresetValue(getSubState(preset, "ScatterloomDSP/grain"));
    this->gen_01_param_ScatterloomDSP_attack_setPresetValue(getSubState(preset, "ScatterloomDSP/attack"));
    this->gen_01_param_ScatterloomDSP_grainCount_setPresetValue(getSubState(preset, "ScatterloomDSP/grainCount"));
    this->gen_01_param_ScatterloomDSP_steps_setPresetValue(getSubState(preset, "ScatterloomDSP/steps"));
    this->gen_01_param_ScatterloomDSP_pulses_setPresetValue(getSubState(preset, "ScatterloomDSP/pulses"));
    this->gen_01_param_ScatterloomDSP_rotation_setPresetValue(getSubState(preset, "ScatterloomDSP/rotation"));
    this->gen_01_param_ScatterloomDSP_feedback_setPresetValue(getSubState(preset, "ScatterloomDSP/feedback"));
    this->gen_01_param_ScatterloomDSP_mixAmount_setPresetValue(getSubState(preset, "ScatterloomDSP/mixAmount"));
    this->gen_01_param_ScatterloomDSP_grainFeedback_setPresetValue(getSubState(preset, "ScatterloomDSP/grainFeedback"));
    this->gen_01_param_ScatterloomDSP_reverseProbability_setPresetValue(getSubState(preset, "ScatterloomDSP/reverseProbability"));
    this->gen_01_param_ScatterloomDSP_clearPool_setPresetValue(getSubState(preset, "ScatterloomDSP/clearPool"));
    this->gen_01_param_ScatterloomDSP_division_setPresetValue(getSubState(preset, "ScatterloomDSP/division"));
    this->gen_01_param_ScatterloomDSP_rotationInterval_setPresetValue(getSubState(preset, "ScatterloomDSP/rotationInterval"));
    this->gen_01_param_ScatterloomDSP_grainPan0_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan0"));
    this->gen_01_param_ScatterloomDSP_grainPan1_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan1"));
    this->gen_01_param_ScatterloomDSP_grainPan2_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan2"));
    this->gen_01_param_ScatterloomDSP_grainPan3_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan3"));
    this->gen_01_param_ScatterloomDSP_grainPan4_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan4"));
    this->gen_01_param_ScatterloomDSP_grainPan5_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan5"));
    this->gen_01_param_ScatterloomDSP_grainPan6_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan6"));
    this->gen_01_param_ScatterloomDSP_grainPan7_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan7"));
    this->gen_01_param_ScatterloomDSP_grainPan8_setPresetValue(getSubState(preset, "ScatterloomDSP/grainPan8"));
    this->gen_01_param_ScatterloomDSP_grainSelectionMode_setPresetValue(getSubState(preset, "ScatterloomDSP/grainSelectionMode"));
    this->gen_01_param_ScatterloomDSP_loopDivision_setPresetValue(getSubState(preset, "ScatterloomDSP/loopDivision"));
    this->gen_01_param_ScatterloomDSP_timingOffset_setPresetValue(getSubState(preset, "ScatterloomDSP/timingOffset"));
    this->gen_01_param_ScatterloomDSP_removeGrain_setPresetValue(getSubState(preset, "ScatterloomDSP/removeGrain"));
    this->gen_01_param_ScatterloomDSP_auditionGrain_setPresetValue(getSubState(preset, "ScatterloomDSP/auditionGrain"));
    this->gen_01_param_ScatterloomDSP_reorderFrom_setPresetValue(getSubState(preset, "ScatterloomDSP/reorderFrom"));
    this->gen_01_param_ScatterloomDSP_reorderTo_setPresetValue(getSubState(preset, "ScatterloomDSP/reorderTo"));
    this->gen_01_param_ScatterloomDSP_reorderCommit_setPresetValue(getSubState(preset, "ScatterloomDSP/reorderCommit"));
    this->gen_01_param_ScatterloomDSP_markovWeight0_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight0"));
    this->gen_01_param_ScatterloomDSP_markovWeight1_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight1"));
    this->gen_01_param_ScatterloomDSP_markovWeight2_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight2"));
    this->gen_01_param_ScatterloomDSP_markovWeight3_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight3"));
    this->gen_01_param_ScatterloomDSP_markovWeight4_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight4"));
    this->gen_01_param_ScatterloomDSP_markovWeight5_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight5"));
    this->gen_01_param_ScatterloomDSP_markovWeight6_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight6"));
    this->gen_01_param_ScatterloomDSP_markovWeight7_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight7"));
    this->gen_01_param_ScatterloomDSP_markovWeight8_setPresetValue(getSubState(preset, "ScatterloomDSP/markovWeight8"));
    this->gen_01_param_ScatterloomDSP_markovEditRow_setPresetValue(getSubState(preset, "ScatterloomDSP/markovEditRow"));
    this->gen_01_param_ScatterloomDSP_markovCommit_setPresetValue(getSubState(preset, "ScatterloomDSP/markovCommit"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 0:
        {
        this->gen_01_param_ScatterloomDSP_sensitivity_value_set(v);
        break;
        }
    case 1:
        {
        this->gen_01_param_ScatterloomDSP_autoSensitivity_value_set(v);
        break;
        }
    case 2:
        {
        this->gen_01_param_ScatterloomDSP_captureOn_value_set(v);
        break;
        }
    case 3:
        {
        this->gen_01_param_ScatterloomDSP_grain_value_set(v);
        break;
        }
    case 4:
        {
        this->gen_01_param_ScatterloomDSP_attack_value_set(v);
        break;
        }
    case 5:
        {
        this->gen_01_param_ScatterloomDSP_grainCount_value_set(v);
        break;
        }
    case 6:
        {
        this->gen_01_param_ScatterloomDSP_steps_value_set(v);
        break;
        }
    case 7:
        {
        this->gen_01_param_ScatterloomDSP_pulses_value_set(v);
        break;
        }
    case 8:
        {
        this->gen_01_param_ScatterloomDSP_rotation_value_set(v);
        break;
        }
    case 9:
        {
        this->gen_01_param_ScatterloomDSP_feedback_value_set(v);
        break;
        }
    case 10:
        {
        this->gen_01_param_ScatterloomDSP_mixAmount_value_set(v);
        break;
        }
    case 11:
        {
        this->gen_01_param_ScatterloomDSP_grainFeedback_value_set(v);
        break;
        }
    case 12:
        {
        this->gen_01_param_ScatterloomDSP_reverseProbability_value_set(v);
        break;
        }
    case 13:
        {
        this->gen_01_param_ScatterloomDSP_clearPool_value_set(v);
        break;
        }
    case 14:
        {
        this->gen_01_param_ScatterloomDSP_division_value_set(v);
        break;
        }
    case 15:
        {
        this->gen_01_param_ScatterloomDSP_rotationInterval_value_set(v);
        break;
        }
    case 16:
        {
        this->gen_01_param_ScatterloomDSP_grainPan0_value_set(v);
        break;
        }
    case 17:
        {
        this->gen_01_param_ScatterloomDSP_grainPan1_value_set(v);
        break;
        }
    case 18:
        {
        this->gen_01_param_ScatterloomDSP_grainPan2_value_set(v);
        break;
        }
    case 19:
        {
        this->gen_01_param_ScatterloomDSP_grainPan3_value_set(v);
        break;
        }
    case 20:
        {
        this->gen_01_param_ScatterloomDSP_grainPan4_value_set(v);
        break;
        }
    case 21:
        {
        this->gen_01_param_ScatterloomDSP_grainPan5_value_set(v);
        break;
        }
    case 22:
        {
        this->gen_01_param_ScatterloomDSP_grainPan6_value_set(v);
        break;
        }
    case 23:
        {
        this->gen_01_param_ScatterloomDSP_grainPan7_value_set(v);
        break;
        }
    case 24:
        {
        this->gen_01_param_ScatterloomDSP_grainPan8_value_set(v);
        break;
        }
    case 25:
        {
        this->gen_01_param_ScatterloomDSP_grainSelectionMode_value_set(v);
        break;
        }
    case 26:
        {
        this->gen_01_param_ScatterloomDSP_loopDivision_value_set(v);
        break;
        }
    case 27:
        {
        this->gen_01_param_ScatterloomDSP_timingOffset_value_set(v);
        break;
        }
    case 28:
        {
        this->gen_01_param_ScatterloomDSP_removeGrain_value_set(v);
        break;
        }
    case 29:
        {
        this->gen_01_param_ScatterloomDSP_auditionGrain_value_set(v);
        break;
        }
    case 30:
        {
        this->gen_01_param_ScatterloomDSP_reorderFrom_value_set(v);
        break;
        }
    case 31:
        {
        this->gen_01_param_ScatterloomDSP_reorderTo_value_set(v);
        break;
        }
    case 32:
        {
        this->gen_01_param_ScatterloomDSP_reorderCommit_value_set(v);
        break;
        }
    case 33:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight0_value_set(v);
        break;
        }
    case 34:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight1_value_set(v);
        break;
        }
    case 35:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight2_value_set(v);
        break;
        }
    case 36:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight3_value_set(v);
        break;
        }
    case 37:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight4_value_set(v);
        break;
        }
    case 38:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight5_value_set(v);
        break;
        }
    case 39:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight6_value_set(v);
        break;
        }
    case 40:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight7_value_set(v);
        break;
        }
    case 41:
        {
        this->gen_01_param_ScatterloomDSP_markovWeight8_value_set(v);
        break;
        }
    case 42:
        {
        this->gen_01_param_ScatterloomDSP_markovEditRow_value_set(v);
        break;
        }
    case 43:
        {
        this->gen_01_param_ScatterloomDSP_markovCommit_value_set(v);
        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->gen_01_param_ScatterloomDSP_sensitivity_value;
        }
    case 1:
        {
        return this->gen_01_param_ScatterloomDSP_autoSensitivity_value;
        }
    case 2:
        {
        return this->gen_01_param_ScatterloomDSP_captureOn_value;
        }
    case 3:
        {
        return this->gen_01_param_ScatterloomDSP_grain_value;
        }
    case 4:
        {
        return this->gen_01_param_ScatterloomDSP_attack_value;
        }
    case 5:
        {
        return this->gen_01_param_ScatterloomDSP_grainCount_value;
        }
    case 6:
        {
        return this->gen_01_param_ScatterloomDSP_steps_value;
        }
    case 7:
        {
        return this->gen_01_param_ScatterloomDSP_pulses_value;
        }
    case 8:
        {
        return this->gen_01_param_ScatterloomDSP_rotation_value;
        }
    case 9:
        {
        return this->gen_01_param_ScatterloomDSP_feedback_value;
        }
    case 10:
        {
        return this->gen_01_param_ScatterloomDSP_mixAmount_value;
        }
    case 11:
        {
        return this->gen_01_param_ScatterloomDSP_grainFeedback_value;
        }
    case 12:
        {
        return this->gen_01_param_ScatterloomDSP_reverseProbability_value;
        }
    case 13:
        {
        return this->gen_01_param_ScatterloomDSP_clearPool_value;
        }
    case 14:
        {
        return this->gen_01_param_ScatterloomDSP_division_value;
        }
    case 15:
        {
        return this->gen_01_param_ScatterloomDSP_rotationInterval_value;
        }
    case 16:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan0_value;
        }
    case 17:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan1_value;
        }
    case 18:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan2_value;
        }
    case 19:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan3_value;
        }
    case 20:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan4_value;
        }
    case 21:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan5_value;
        }
    case 22:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan6_value;
        }
    case 23:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan7_value;
        }
    case 24:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan8_value;
        }
    case 25:
        {
        return this->gen_01_param_ScatterloomDSP_grainSelectionMode_value;
        }
    case 26:
        {
        return this->gen_01_param_ScatterloomDSP_loopDivision_value;
        }
    case 27:
        {
        return this->gen_01_param_ScatterloomDSP_timingOffset_value;
        }
    case 28:
        {
        return this->gen_01_param_ScatterloomDSP_removeGrain_value;
        }
    case 29:
        {
        return this->gen_01_param_ScatterloomDSP_auditionGrain_value;
        }
    case 30:
        {
        return this->gen_01_param_ScatterloomDSP_reorderFrom_value;
        }
    case 31:
        {
        return this->gen_01_param_ScatterloomDSP_reorderTo_value;
        }
    case 32:
        {
        return this->gen_01_param_ScatterloomDSP_reorderCommit_value;
        }
    case 33:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight0_value;
        }
    case 34:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight1_value;
        }
    case 35:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight2_value;
        }
    case 36:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight3_value;
        }
    case 37:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight4_value;
        }
    case 38:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight5_value;
        }
    case 39:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight6_value;
        }
    case 40:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight7_value;
        }
    case 41:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight8_value;
        }
    case 42:
        {
        return this->gen_01_param_ScatterloomDSP_markovEditRow_value;
        }
    case 43:
        {
        return this->gen_01_param_ScatterloomDSP_markovCommit_value;
        }
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 44;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "ScatterloomDSP/sensitivity";
        }
    case 1:
        {
        return "ScatterloomDSP/autoSensitivity";
        }
    case 2:
        {
        return "ScatterloomDSP/captureOn";
        }
    case 3:
        {
        return "ScatterloomDSP/grain";
        }
    case 4:
        {
        return "ScatterloomDSP/attack";
        }
    case 5:
        {
        return "ScatterloomDSP/grainCount";
        }
    case 6:
        {
        return "ScatterloomDSP/steps";
        }
    case 7:
        {
        return "ScatterloomDSP/pulses";
        }
    case 8:
        {
        return "ScatterloomDSP/rotation";
        }
    case 9:
        {
        return "ScatterloomDSP/feedback";
        }
    case 10:
        {
        return "ScatterloomDSP/mixAmount";
        }
    case 11:
        {
        return "ScatterloomDSP/grainFeedback";
        }
    case 12:
        {
        return "ScatterloomDSP/reverseProbability";
        }
    case 13:
        {
        return "ScatterloomDSP/clearPool";
        }
    case 14:
        {
        return "ScatterloomDSP/division";
        }
    case 15:
        {
        return "ScatterloomDSP/rotationInterval";
        }
    case 16:
        {
        return "ScatterloomDSP/grainPan0";
        }
    case 17:
        {
        return "ScatterloomDSP/grainPan1";
        }
    case 18:
        {
        return "ScatterloomDSP/grainPan2";
        }
    case 19:
        {
        return "ScatterloomDSP/grainPan3";
        }
    case 20:
        {
        return "ScatterloomDSP/grainPan4";
        }
    case 21:
        {
        return "ScatterloomDSP/grainPan5";
        }
    case 22:
        {
        return "ScatterloomDSP/grainPan6";
        }
    case 23:
        {
        return "ScatterloomDSP/grainPan7";
        }
    case 24:
        {
        return "ScatterloomDSP/grainPan8";
        }
    case 25:
        {
        return "ScatterloomDSP/grainSelectionMode";
        }
    case 26:
        {
        return "ScatterloomDSP/loopDivision";
        }
    case 27:
        {
        return "ScatterloomDSP/timingOffset";
        }
    case 28:
        {
        return "ScatterloomDSP/removeGrain";
        }
    case 29:
        {
        return "ScatterloomDSP/auditionGrain";
        }
    case 30:
        {
        return "ScatterloomDSP/reorderFrom";
        }
    case 31:
        {
        return "ScatterloomDSP/reorderTo";
        }
    case 32:
        {
        return "ScatterloomDSP/reorderCommit";
        }
    case 33:
        {
        return "ScatterloomDSP/markovWeight0";
        }
    case 34:
        {
        return "ScatterloomDSP/markovWeight1";
        }
    case 35:
        {
        return "ScatterloomDSP/markovWeight2";
        }
    case 36:
        {
        return "ScatterloomDSP/markovWeight3";
        }
    case 37:
        {
        return "ScatterloomDSP/markovWeight4";
        }
    case 38:
        {
        return "ScatterloomDSP/markovWeight5";
        }
    case 39:
        {
        return "ScatterloomDSP/markovWeight6";
        }
    case 40:
        {
        return "ScatterloomDSP/markovWeight7";
        }
    case 41:
        {
        return "ScatterloomDSP/markovWeight8";
        }
    case 42:
        {
        return "ScatterloomDSP/markovEditRow";
        }
    case 43:
        {
        return "ScatterloomDSP/markovCommit";
        }
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "ScatterloomDSP/sensitivity";
        }
    case 1:
        {
        return "ScatterloomDSP/autoSensitivity";
        }
    case 2:
        {
        return "ScatterloomDSP/captureOn";
        }
    case 3:
        {
        return "ScatterloomDSP/grain";
        }
    case 4:
        {
        return "ScatterloomDSP/attack";
        }
    case 5:
        {
        return "ScatterloomDSP/grainCount";
        }
    case 6:
        {
        return "ScatterloomDSP/steps";
        }
    case 7:
        {
        return "ScatterloomDSP/pulses";
        }
    case 8:
        {
        return "ScatterloomDSP/rotation";
        }
    case 9:
        {
        return "ScatterloomDSP/feedback";
        }
    case 10:
        {
        return "ScatterloomDSP/mixAmount";
        }
    case 11:
        {
        return "ScatterloomDSP/grainFeedback";
        }
    case 12:
        {
        return "ScatterloomDSP/reverseProbability";
        }
    case 13:
        {
        return "ScatterloomDSP/clearPool";
        }
    case 14:
        {
        return "ScatterloomDSP/division";
        }
    case 15:
        {
        return "ScatterloomDSP/rotationInterval";
        }
    case 16:
        {
        return "ScatterloomDSP/grainPan0";
        }
    case 17:
        {
        return "ScatterloomDSP/grainPan1";
        }
    case 18:
        {
        return "ScatterloomDSP/grainPan2";
        }
    case 19:
        {
        return "ScatterloomDSP/grainPan3";
        }
    case 20:
        {
        return "ScatterloomDSP/grainPan4";
        }
    case 21:
        {
        return "ScatterloomDSP/grainPan5";
        }
    case 22:
        {
        return "ScatterloomDSP/grainPan6";
        }
    case 23:
        {
        return "ScatterloomDSP/grainPan7";
        }
    case 24:
        {
        return "ScatterloomDSP/grainPan8";
        }
    case 25:
        {
        return "ScatterloomDSP/grainSelectionMode";
        }
    case 26:
        {
        return "ScatterloomDSP/loopDivision";
        }
    case 27:
        {
        return "ScatterloomDSP/timingOffset";
        }
    case 28:
        {
        return "ScatterloomDSP/removeGrain";
        }
    case 29:
        {
        return "ScatterloomDSP/auditionGrain";
        }
    case 30:
        {
        return "ScatterloomDSP/reorderFrom";
        }
    case 31:
        {
        return "ScatterloomDSP/reorderTo";
        }
    case 32:
        {
        return "ScatterloomDSP/reorderCommit";
        }
    case 33:
        {
        return "ScatterloomDSP/markovWeight0";
        }
    case 34:
        {
        return "ScatterloomDSP/markovWeight1";
        }
    case 35:
        {
        return "ScatterloomDSP/markovWeight2";
        }
    case 36:
        {
        return "ScatterloomDSP/markovWeight3";
        }
    case 37:
        {
        return "ScatterloomDSP/markovWeight4";
        }
    case 38:
        {
        return "ScatterloomDSP/markovWeight5";
        }
    case 39:
        {
        return "ScatterloomDSP/markovWeight6";
        }
    case 40:
        {
        return "ScatterloomDSP/markovWeight7";
        }
    case 41:
        {
        return "ScatterloomDSP/markovWeight8";
        }
    case 42:
        {
        return "ScatterloomDSP/markovEditRow";
        }
    case 43:
        {
        return "ScatterloomDSP/markovCommit";
        }
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.35;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Sensitivity";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Auto Sensitivity";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Capture";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.33;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Length";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Attack";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 5;
            info->min = 1;
            info->max = 9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Recent Grains";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 16;
            info->min = 1;
            info->max = 32;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Steps";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 5;
            info->min = 0;
            info->max = 32;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Pulses";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 31;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Rotate";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.35;
            info->min = 0;
            info->max = 1.15;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Loop Feedback";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Mix";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1.15;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Feedback";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Reverse Chance";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Clear Pool";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 14:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 10;
            info->min = 0;
            info->max = 13;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Division";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 15:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 13;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Rotation Mode";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 16:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = -0.5;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 1";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 17:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 2";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 18:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = -0.25;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 3";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 19:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.25;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 4";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 20:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 5";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 21:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = -0.375;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 6";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 22:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.375;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 7";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 23:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = -0.125;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 8";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 24:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.125;
            info->min = -1;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Pan 9";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 25:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 2;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Order Engine";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 26:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 4;
            info->min = 0;
            info->max = 13;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Loop Time";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 27:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -0.2;
            info->max = 0.2;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Grain Start";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 28:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Remove Grain";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 29:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Audition Grain";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 30:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Reorder From";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 31:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Reorder To";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 32:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Reorder";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 33:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 1";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 34:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 2";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 35:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 3";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 36:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 4";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 37:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 5";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 38:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 6";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 39:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 7";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 40:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 8";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 41:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.111111;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Weight 9";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 42:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 8;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Row";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 43:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Weave Commit";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        }
    }
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 10:
    case 12:
    case 13:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 43:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 25:
        {
        {
            value = (value < 0 ? 0 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0) / (2 - 0);
            return normalizedValue;
        }
        }
    case 42:
        {
        {
            value = (value < 0 ? 0 : (value > 8 ? 8 : value));
            ParameterValue normalizedValue = (value - 0) / (8 - 0);
            return normalizedValue;
        }
        }
    case 28:
    case 29:
    case 30:
    case 31:
        {
        {
            value = (value < 0 ? 0 : (value > 9 ? 9 : value));
            ParameterValue normalizedValue = (value - 0) / (9 - 0);
            return normalizedValue;
        }
        }
    case 14:
    case 15:
    case 26:
        {
        {
            value = (value < 0 ? 0 : (value > 13 ? 13 : value));
            ParameterValue normalizedValue = (value - 0) / (13 - 0);
            return normalizedValue;
        }
        }
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 31 ? 31 : value));
            ParameterValue normalizedValue = (value - 0) / (31 - 0);
            return normalizedValue;
        }
        }
    case 7:
        {
        {
            value = (value < 0 ? 0 : (value > 32 ? 32 : value));
            ParameterValue normalizedValue = (value - 0) / (32 - 0);
            return normalizedValue;
        }
        }
    case 9:
    case 11:
        {
        {
            value = (value < 0 ? 0 : (value > 1.15 ? 1.15 : value));
            ParameterValue normalizedValue = (value - 0) / (1.15 - 0);
            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 1 ? 1 : (value > 9 ? 9 : value));
            ParameterValue normalizedValue = (value - 1) / (9 - 1);
            return normalizedValue;
        }
        }
    case 6:
        {
        {
            value = (value < 1 ? 1 : (value > 32 ? 32 : value));
            ParameterValue normalizedValue = (value - 1) / (32 - 1);
            return normalizedValue;
        }
        }
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        {
        {
            value = (value < -1 ? -1 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - -1) / (1 - -1);
            return normalizedValue;
        }
        }
    case 27:
        {
        {
            value = (value < -0.2 ? -0.2 : (value > 0.2 ? 0.2 : value));
            ParameterValue normalizedValue = (value - -0.2) / (0.2 - -0.2);
            return normalizedValue;
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 10:
    case 12:
    case 13:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 43:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 25:
        {
        {
            {
                return 0 + value * (2 - 0);
            }
        }
        }
    case 42:
        {
        {
            {
                return 0 + value * (8 - 0);
            }
        }
        }
    case 28:
    case 29:
    case 30:
    case 31:
        {
        {
            {
                return 0 + value * (9 - 0);
            }
        }
        }
    case 14:
    case 15:
    case 26:
        {
        {
            {
                return 0 + value * (13 - 0);
            }
        }
        }
    case 8:
        {
        {
            {
                return 0 + value * (31 - 0);
            }
        }
        }
    case 7:
        {
        {
            {
                return 0 + value * (32 - 0);
            }
        }
        }
    case 9:
    case 11:
        {
        {
            {
                return 0 + value * (1.15 - 0);
            }
        }
        }
    case 5:
        {
        {
            {
                return 1 + value * (9 - 1);
            }
        }
        }
    case 6:
        {
        {
            {
                return 1 + value * (32 - 1);
            }
        }
        }
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        {
        {
            {
                return -1 + value * (1 - -1);
            }
        }
        }
    case 27:
        {
        {
            {
                return -0.2 + value * (0.2 - -0.2);
            }
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->gen_01_param_ScatterloomDSP_sensitivity_value_constrain(value);
        }
    case 1:
        {
        return this->gen_01_param_ScatterloomDSP_autoSensitivity_value_constrain(value);
        }
    case 2:
        {
        return this->gen_01_param_ScatterloomDSP_captureOn_value_constrain(value);
        }
    case 3:
        {
        return this->gen_01_param_ScatterloomDSP_grain_value_constrain(value);
        }
    case 4:
        {
        return this->gen_01_param_ScatterloomDSP_attack_value_constrain(value);
        }
    case 5:
        {
        return this->gen_01_param_ScatterloomDSP_grainCount_value_constrain(value);
        }
    case 6:
        {
        return this->gen_01_param_ScatterloomDSP_steps_value_constrain(value);
        }
    case 7:
        {
        return this->gen_01_param_ScatterloomDSP_pulses_value_constrain(value);
        }
    case 8:
        {
        return this->gen_01_param_ScatterloomDSP_rotation_value_constrain(value);
        }
    case 9:
        {
        return this->gen_01_param_ScatterloomDSP_feedback_value_constrain(value);
        }
    case 10:
        {
        return this->gen_01_param_ScatterloomDSP_mixAmount_value_constrain(value);
        }
    case 11:
        {
        return this->gen_01_param_ScatterloomDSP_grainFeedback_value_constrain(value);
        }
    case 12:
        {
        return this->gen_01_param_ScatterloomDSP_reverseProbability_value_constrain(value);
        }
    case 13:
        {
        return this->gen_01_param_ScatterloomDSP_clearPool_value_constrain(value);
        }
    case 14:
        {
        return this->gen_01_param_ScatterloomDSP_division_value_constrain(value);
        }
    case 15:
        {
        return this->gen_01_param_ScatterloomDSP_rotationInterval_value_constrain(value);
        }
    case 16:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan0_value_constrain(value);
        }
    case 17:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan1_value_constrain(value);
        }
    case 18:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan2_value_constrain(value);
        }
    case 19:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan3_value_constrain(value);
        }
    case 20:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan4_value_constrain(value);
        }
    case 21:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan5_value_constrain(value);
        }
    case 22:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan6_value_constrain(value);
        }
    case 23:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan7_value_constrain(value);
        }
    case 24:
        {
        return this->gen_01_param_ScatterloomDSP_grainPan8_value_constrain(value);
        }
    case 25:
        {
        return this->gen_01_param_ScatterloomDSP_grainSelectionMode_value_constrain(value);
        }
    case 26:
        {
        return this->gen_01_param_ScatterloomDSP_loopDivision_value_constrain(value);
        }
    case 27:
        {
        return this->gen_01_param_ScatterloomDSP_timingOffset_value_constrain(value);
        }
    case 28:
        {
        return this->gen_01_param_ScatterloomDSP_removeGrain_value_constrain(value);
        }
    case 29:
        {
        return this->gen_01_param_ScatterloomDSP_auditionGrain_value_constrain(value);
        }
    case 30:
        {
        return this->gen_01_param_ScatterloomDSP_reorderFrom_value_constrain(value);
        }
    case 31:
        {
        return this->gen_01_param_ScatterloomDSP_reorderTo_value_constrain(value);
        }
    case 32:
        {
        return this->gen_01_param_ScatterloomDSP_reorderCommit_value_constrain(value);
        }
    case 33:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight0_value_constrain(value);
        }
    case 34:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight1_value_constrain(value);
        }
    case 35:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight2_value_constrain(value);
        }
    case 36:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight3_value_constrain(value);
        }
    case 37:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight4_value_constrain(value);
        }
    case 38:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight5_value_constrain(value);
        }
    case 39:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight6_value_constrain(value);
        }
    case 40:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight7_value_constrain(value);
        }
    case 41:
        {
        return this->gen_01_param_ScatterloomDSP_markovWeight8_value_constrain(value);
        }
    case 42:
        {
        return this->gen_01_param_ScatterloomDSP_markovEditRow_value_constrain(value);
        }
    case 43:
        {
        return this->gen_01_param_ScatterloomDSP_markovCommit_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}

void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}

void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(inProcess ? time + sampsToMs(this->vs) : time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a1 = 1. + a;
    number aa = a * a1;
    number b = 1. - a;
    number b1 = 2. - a;
    number bb = b * b1;
    number fw = -.1666667 * bb * a;
    number fx = .5 * bb * a1;
    number fy = .5 * aa * b1;
    number fz = -.1666667 * aa * b;
    return w * fw + x * fx + y * fy + z * fz;
}

inline number fastcubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
    number ym2py2 = y0 + y4;
    number ym1py1 = y1 + y3;
    number y2mym2 = y4 - y0;
    number y1mym1 = y3 - y1;
    number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
    number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
    number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
    number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
    number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
    number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
    number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
    return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number minimum(number x, number y) {
    return (y < x ? y : x);
}

number __wrapped_op_clamp(number in1, number in2, number in3) {
    return (in1 > in3 ? in3 : (in1 < in2 ? in2 : in1));
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

number wrap(number x, number low, number high) {
    number lo;
    number hi;

    if (low == high)
        return low;

    if (low > high) {
        hi = low;
        lo = high;
    } else {
        lo = low;
        hi = high;
    }

    number range = hi - lo;

    if (x >= lo && x < hi)
        return x;

    if (range <= 0.000000001)
        return lo;

    Int numWraps = (Int)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

template<typename BUFFERTYPE> array<SampleValue, 1 + 1> peek_default(BUFFERTYPE& buffer, SampleValue sampleIndex, Index channelOffset) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());
    constexpr int ___N2 = 1 + 1;
    array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);

    if (bufferSize == 0 || (5 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
        return out;
    } else {
        for (Index channel = 0; channel < 1; channel++) {
            Index channelIndex = (Index)(channel + channelOffset);

            {
                if (channelIndex >= bufferChannels || channelIndex < 0) {
                    out[(Index)channel] = 0;
                    continue;
                }
            }

            SampleValue bufferreadsample_result;

            {
                auto& __buffer = buffer;

                if (sampleIndex < 0.0) {
                    bufferreadsample_result = 0.0;
                }

                SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));

                {
                    bufferreadsample_result = __buffer->getSample(channelIndex, truncIndex);
                }
            }

            out[(Index)channel] = bufferreadsample_result;
        }

        out[1] = sampleIndex;
        return out;
    }
}

template<typename BUFFERTYPE> void poke_default(
    BUFFERTYPE& buffer,
    SampleValue value,
    SampleValue sampleIndex,
    Int channel,
    number overdub
) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());

    if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
        if (overdub != 0) {
            number currentValue = buffer->getSample(channel, sampleIndex);

            {
                value = value + currentValue * overdub;
            }
        }

        buffer->setSample(channel, sampleIndex, value);
        buffer->setTouched(true);
    }
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->_currentTime);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

void gen_01_param_ScatterloomDSP_sensitivity_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_sensitivity_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_sensitivity_value = v;
    this->sendParameter(0, false);

    if (this->gen_01_param_ScatterloomDSP_sensitivity_value != this->gen_01_param_ScatterloomDSP_sensitivity_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_sensitivity_lastValue = this->gen_01_param_ScatterloomDSP_sensitivity_value;
    }

    this->gen_01_sensitivity_set(v);
}

void gen_01_param_ScatterloomDSP_autoSensitivity_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_autoSensitivity_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_autoSensitivity_value = v;
    this->sendParameter(1, false);

    if (this->gen_01_param_ScatterloomDSP_autoSensitivity_value != this->gen_01_param_ScatterloomDSP_autoSensitivity_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_autoSensitivity_lastValue = this->gen_01_param_ScatterloomDSP_autoSensitivity_value;
    }

    this->gen_01_autoSensitivity_set(v);
}

void gen_01_param_ScatterloomDSP_captureOn_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_captureOn_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_captureOn_value = v;
    this->sendParameter(2, false);

    if (this->gen_01_param_ScatterloomDSP_captureOn_value != this->gen_01_param_ScatterloomDSP_captureOn_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_captureOn_lastValue = this->gen_01_param_ScatterloomDSP_captureOn_value;
    }

    this->gen_01_captureOn_set(v);
}

void gen_01_param_ScatterloomDSP_grain_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grain_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grain_value = v;
    this->sendParameter(3, false);

    if (this->gen_01_param_ScatterloomDSP_grain_value != this->gen_01_param_ScatterloomDSP_grain_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grain_lastValue = this->gen_01_param_ScatterloomDSP_grain_value;
    }

    this->gen_01_grain_set(v);
}

void gen_01_param_ScatterloomDSP_attack_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_attack_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_attack_value = v;
    this->sendParameter(4, false);

    if (this->gen_01_param_ScatterloomDSP_attack_value != this->gen_01_param_ScatterloomDSP_attack_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_attack_lastValue = this->gen_01_param_ScatterloomDSP_attack_value;
    }

    this->gen_01_attack_set(v);
}

void gen_01_param_ScatterloomDSP_grainCount_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainCount_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainCount_value = v;
    this->sendParameter(5, false);

    if (this->gen_01_param_ScatterloomDSP_grainCount_value != this->gen_01_param_ScatterloomDSP_grainCount_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainCount_lastValue = this->gen_01_param_ScatterloomDSP_grainCount_value;
    }

    this->gen_01_grainCount_set(v);
}

void gen_01_param_ScatterloomDSP_steps_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_steps_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_steps_value = v;
    this->sendParameter(6, false);

    if (this->gen_01_param_ScatterloomDSP_steps_value != this->gen_01_param_ScatterloomDSP_steps_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_steps_lastValue = this->gen_01_param_ScatterloomDSP_steps_value;
    }

    this->gen_01_steps_set(v);
}

void gen_01_param_ScatterloomDSP_pulses_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_pulses_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_pulses_value = v;
    this->sendParameter(7, false);

    if (this->gen_01_param_ScatterloomDSP_pulses_value != this->gen_01_param_ScatterloomDSP_pulses_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_pulses_lastValue = this->gen_01_param_ScatterloomDSP_pulses_value;
    }

    this->gen_01_pulses_set(v);
}

void gen_01_param_ScatterloomDSP_rotation_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_rotation_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_rotation_value = v;
    this->sendParameter(8, false);

    if (this->gen_01_param_ScatterloomDSP_rotation_value != this->gen_01_param_ScatterloomDSP_rotation_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_rotation_lastValue = this->gen_01_param_ScatterloomDSP_rotation_value;
    }

    this->gen_01_rotation_set(v);
}

void gen_01_param_ScatterloomDSP_feedback_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_feedback_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_feedback_value = v;
    this->sendParameter(9, false);

    if (this->gen_01_param_ScatterloomDSP_feedback_value != this->gen_01_param_ScatterloomDSP_feedback_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_feedback_lastValue = this->gen_01_param_ScatterloomDSP_feedback_value;
    }

    this->gen_01_feedback_set(v);
}

void gen_01_param_ScatterloomDSP_mixAmount_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_mixAmount_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_mixAmount_value = v;
    this->sendParameter(10, false);

    if (this->gen_01_param_ScatterloomDSP_mixAmount_value != this->gen_01_param_ScatterloomDSP_mixAmount_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_mixAmount_lastValue = this->gen_01_param_ScatterloomDSP_mixAmount_value;
    }

    this->gen_01_mixAmount_set(v);
}

void gen_01_param_ScatterloomDSP_grainFeedback_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainFeedback_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainFeedback_value = v;
    this->sendParameter(11, false);

    if (this->gen_01_param_ScatterloomDSP_grainFeedback_value != this->gen_01_param_ScatterloomDSP_grainFeedback_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainFeedback_lastValue = this->gen_01_param_ScatterloomDSP_grainFeedback_value;
    }

    this->gen_01_grainFeedback_set(v);
}

void gen_01_param_ScatterloomDSP_reverseProbability_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_reverseProbability_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_reverseProbability_value = v;
    this->sendParameter(12, false);

    if (this->gen_01_param_ScatterloomDSP_reverseProbability_value != this->gen_01_param_ScatterloomDSP_reverseProbability_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_reverseProbability_lastValue = this->gen_01_param_ScatterloomDSP_reverseProbability_value;
    }

    this->gen_01_reverseProbability_set(v);
}

void gen_01_param_ScatterloomDSP_clearPool_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_clearPool_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_clearPool_value = v;
    this->sendParameter(13, false);

    if (this->gen_01_param_ScatterloomDSP_clearPool_value != this->gen_01_param_ScatterloomDSP_clearPool_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_clearPool_lastValue = this->gen_01_param_ScatterloomDSP_clearPool_value;
    }

    this->gen_01_clearPool_set(v);
}

void gen_01_param_ScatterloomDSP_division_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_division_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_division_value = v;
    this->sendParameter(14, false);

    if (this->gen_01_param_ScatterloomDSP_division_value != this->gen_01_param_ScatterloomDSP_division_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_division_lastValue = this->gen_01_param_ScatterloomDSP_division_value;
    }

    this->gen_01_division_set(v);
}

void gen_01_param_ScatterloomDSP_rotationInterval_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_rotationInterval_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_rotationInterval_value = v;
    this->sendParameter(15, false);

    if (this->gen_01_param_ScatterloomDSP_rotationInterval_value != this->gen_01_param_ScatterloomDSP_rotationInterval_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_rotationInterval_lastValue = this->gen_01_param_ScatterloomDSP_rotationInterval_value;
    }

    this->gen_01_rotationInterval_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan0_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan0_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan0_value = v;
    this->sendParameter(16, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan0_value != this->gen_01_param_ScatterloomDSP_grainPan0_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan0_lastValue = this->gen_01_param_ScatterloomDSP_grainPan0_value;
    }

    this->gen_01_grainPan0_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan1_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan1_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan1_value = v;
    this->sendParameter(17, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan1_value != this->gen_01_param_ScatterloomDSP_grainPan1_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan1_lastValue = this->gen_01_param_ScatterloomDSP_grainPan1_value;
    }

    this->gen_01_grainPan1_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan2_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan2_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan2_value = v;
    this->sendParameter(18, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan2_value != this->gen_01_param_ScatterloomDSP_grainPan2_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan2_lastValue = this->gen_01_param_ScatterloomDSP_grainPan2_value;
    }

    this->gen_01_grainPan2_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan3_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan3_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan3_value = v;
    this->sendParameter(19, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan3_value != this->gen_01_param_ScatterloomDSP_grainPan3_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan3_lastValue = this->gen_01_param_ScatterloomDSP_grainPan3_value;
    }

    this->gen_01_grainPan3_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan4_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan4_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan4_value = v;
    this->sendParameter(20, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan4_value != this->gen_01_param_ScatterloomDSP_grainPan4_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan4_lastValue = this->gen_01_param_ScatterloomDSP_grainPan4_value;
    }

    this->gen_01_grainPan4_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan5_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan5_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan5_value = v;
    this->sendParameter(21, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan5_value != this->gen_01_param_ScatterloomDSP_grainPan5_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan5_lastValue = this->gen_01_param_ScatterloomDSP_grainPan5_value;
    }

    this->gen_01_grainPan5_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan6_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan6_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan6_value = v;
    this->sendParameter(22, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan6_value != this->gen_01_param_ScatterloomDSP_grainPan6_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan6_lastValue = this->gen_01_param_ScatterloomDSP_grainPan6_value;
    }

    this->gen_01_grainPan6_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan7_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan7_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan7_value = v;
    this->sendParameter(23, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan7_value != this->gen_01_param_ScatterloomDSP_grainPan7_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan7_lastValue = this->gen_01_param_ScatterloomDSP_grainPan7_value;
    }

    this->gen_01_grainPan7_set(v);
}

void gen_01_param_ScatterloomDSP_grainPan8_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainPan8_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainPan8_value = v;
    this->sendParameter(24, false);

    if (this->gen_01_param_ScatterloomDSP_grainPan8_value != this->gen_01_param_ScatterloomDSP_grainPan8_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainPan8_lastValue = this->gen_01_param_ScatterloomDSP_grainPan8_value;
    }

    this->gen_01_grainPan8_set(v);
}

void gen_01_param_ScatterloomDSP_grainSelectionMode_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_grainSelectionMode_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_grainSelectionMode_value = v;
    this->sendParameter(25, false);

    if (this->gen_01_param_ScatterloomDSP_grainSelectionMode_value != this->gen_01_param_ScatterloomDSP_grainSelectionMode_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_grainSelectionMode_lastValue = this->gen_01_param_ScatterloomDSP_grainSelectionMode_value;
    }

    this->gen_01_grainSelectionMode_set(v);
}

void gen_01_param_ScatterloomDSP_loopDivision_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_loopDivision_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_loopDivision_value = v;
    this->sendParameter(26, false);

    if (this->gen_01_param_ScatterloomDSP_loopDivision_value != this->gen_01_param_ScatterloomDSP_loopDivision_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_loopDivision_lastValue = this->gen_01_param_ScatterloomDSP_loopDivision_value;
    }

    this->gen_01_loopDivision_set(v);
}

void gen_01_param_ScatterloomDSP_timingOffset_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_timingOffset_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_timingOffset_value = v;
    this->sendParameter(27, false);

    if (this->gen_01_param_ScatterloomDSP_timingOffset_value != this->gen_01_param_ScatterloomDSP_timingOffset_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_timingOffset_lastValue = this->gen_01_param_ScatterloomDSP_timingOffset_value;
    }

    this->gen_01_timingOffset_set(v);
}

void gen_01_param_ScatterloomDSP_removeGrain_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_removeGrain_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_removeGrain_value = v;
    this->sendParameter(28, false);

    if (this->gen_01_param_ScatterloomDSP_removeGrain_value != this->gen_01_param_ScatterloomDSP_removeGrain_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_removeGrain_lastValue = this->gen_01_param_ScatterloomDSP_removeGrain_value;
    }

    this->gen_01_removeGrain_set(v);
}

void gen_01_param_ScatterloomDSP_auditionGrain_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_auditionGrain_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_auditionGrain_value = v;
    this->sendParameter(29, false);

    if (this->gen_01_param_ScatterloomDSP_auditionGrain_value != this->gen_01_param_ScatterloomDSP_auditionGrain_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_auditionGrain_lastValue = this->gen_01_param_ScatterloomDSP_auditionGrain_value;
    }

    this->gen_01_auditionGrain_set(v);
}

void gen_01_param_ScatterloomDSP_reorderFrom_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_reorderFrom_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_reorderFrom_value = v;
    this->sendParameter(30, false);

    if (this->gen_01_param_ScatterloomDSP_reorderFrom_value != this->gen_01_param_ScatterloomDSP_reorderFrom_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_reorderFrom_lastValue = this->gen_01_param_ScatterloomDSP_reorderFrom_value;
    }

    this->gen_01_reorderFrom_set(v);
}

void gen_01_param_ScatterloomDSP_reorderTo_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_reorderTo_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_reorderTo_value = v;
    this->sendParameter(31, false);

    if (this->gen_01_param_ScatterloomDSP_reorderTo_value != this->gen_01_param_ScatterloomDSP_reorderTo_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_reorderTo_lastValue = this->gen_01_param_ScatterloomDSP_reorderTo_value;
    }

    this->gen_01_reorderTo_set(v);
}

void gen_01_param_ScatterloomDSP_reorderCommit_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_reorderCommit_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_reorderCommit_value = v;
    this->sendParameter(32, false);

    if (this->gen_01_param_ScatterloomDSP_reorderCommit_value != this->gen_01_param_ScatterloomDSP_reorderCommit_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_reorderCommit_lastValue = this->gen_01_param_ScatterloomDSP_reorderCommit_value;
    }

    this->gen_01_reorderCommit_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight0_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight0_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight0_value = v;
    this->sendParameter(33, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight0_value != this->gen_01_param_ScatterloomDSP_markovWeight0_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight0_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight0_value;
    }

    this->gen_01_markovWeight0_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight1_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight1_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight1_value = v;
    this->sendParameter(34, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight1_value != this->gen_01_param_ScatterloomDSP_markovWeight1_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight1_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight1_value;
    }

    this->gen_01_markovWeight1_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight2_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight2_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight2_value = v;
    this->sendParameter(35, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight2_value != this->gen_01_param_ScatterloomDSP_markovWeight2_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight2_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight2_value;
    }

    this->gen_01_markovWeight2_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight3_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight3_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight3_value = v;
    this->sendParameter(36, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight3_value != this->gen_01_param_ScatterloomDSP_markovWeight3_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight3_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight3_value;
    }

    this->gen_01_markovWeight3_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight4_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight4_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight4_value = v;
    this->sendParameter(37, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight4_value != this->gen_01_param_ScatterloomDSP_markovWeight4_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight4_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight4_value;
    }

    this->gen_01_markovWeight4_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight5_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight5_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight5_value = v;
    this->sendParameter(38, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight5_value != this->gen_01_param_ScatterloomDSP_markovWeight5_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight5_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight5_value;
    }

    this->gen_01_markovWeight5_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight6_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight6_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight6_value = v;
    this->sendParameter(39, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight6_value != this->gen_01_param_ScatterloomDSP_markovWeight6_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight6_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight6_value;
    }

    this->gen_01_markovWeight6_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight7_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight7_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight7_value = v;
    this->sendParameter(40, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight7_value != this->gen_01_param_ScatterloomDSP_markovWeight7_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight7_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight7_value;
    }

    this->gen_01_markovWeight7_set(v);
}

void gen_01_param_ScatterloomDSP_markovWeight8_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovWeight8_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovWeight8_value = v;
    this->sendParameter(41, false);

    if (this->gen_01_param_ScatterloomDSP_markovWeight8_value != this->gen_01_param_ScatterloomDSP_markovWeight8_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovWeight8_lastValue = this->gen_01_param_ScatterloomDSP_markovWeight8_value;
    }

    this->gen_01_markovWeight8_set(v);
}

void gen_01_param_ScatterloomDSP_markovEditRow_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovEditRow_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovEditRow_value = v;
    this->sendParameter(42, false);

    if (this->gen_01_param_ScatterloomDSP_markovEditRow_value != this->gen_01_param_ScatterloomDSP_markovEditRow_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovEditRow_lastValue = this->gen_01_param_ScatterloomDSP_markovEditRow_value;
    }

    this->gen_01_markovEditRow_set(v);
}

void gen_01_param_ScatterloomDSP_markovCommit_value_set(number v) {
    v = this->gen_01_param_ScatterloomDSP_markovCommit_value_constrain(v);
    this->gen_01_param_ScatterloomDSP_markovCommit_value = v;
    this->sendParameter(43, false);

    if (this->gen_01_param_ScatterloomDSP_markovCommit_value != this->gen_01_param_ScatterloomDSP_markovCommit_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->gen_01_param_ScatterloomDSP_markovCommit_lastValue = this->gen_01_param_ScatterloomDSP_markovCommit_value;
    }

    this->gen_01_markovCommit_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 1; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->globaltransport_tempo = freeSignal(this->globaltransport_tempo);
    this->globaltransport_state = freeSignal(this->globaltransport_state);
    this->zeroBuffer = freeSignal(this->zeroBuffer);
    this->dummyBuffer = freeSignal(this->dummyBuffer);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

void setProbingTarget(MessageTag ) {}

void fillDataRef(DataRefIndex , DataRef& ) {}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void allocateDataRefs() {
    this->gen_01_markovMatrixB_70->requestSize(81, 1);
    this->gen_01_markovMatrixB_70->setSampleRate(this->sr);
    this->gen_01_markovMatrixA_69->requestSize(81, 1);
    this->gen_01_markovMatrixA_69->setSampleRate(this->sr);
    this->gen_01_trimEnds_68->requestSize(9, 1);
    this->gen_01_trimEnds_68->setSampleRate(this->sr);
    this->gen_01_trimStarts_67->requestSize(9, 1);
    this->gen_01_trimStarts_67->setSampleRate(this->sr);
    this->gen_01_grainLevels_66->requestSize(9, 1);
    this->gen_01_grainLevels_66->setSampleRate(this->sr);
    this->gen_01_captureActive_65->requestSize(9, 1);
    this->gen_01_captureActive_65->setSampleRate(this->sr);
    this->gen_01_capturePositions_64->requestSize(9, 1);
    this->gen_01_capturePositions_64->setSampleRate(this->sr);
    this->gen_01_grainQueue_63->requestSize(9, 1);
    this->gen_01_grainQueue_63->setSampleRate(this->sr);
    this->gen_01_poolR_62->requestSize(2359296, 1);
    this->gen_01_poolR_62->setSampleRate(this->sr);
    this->gen_01_poolL_61->requestSize(2359296, 1);
    this->gen_01_poolL_61->setSampleRate(this->sr);
    this->gen_01_markovMatrixB_70 = this->gen_01_markovMatrixB_70->allocateIfNeeded();

    if (this->markovMatrixB_70->hasRequestedSize()) {
        if (this->markovMatrixB_70->wantsFill())
            this->zeroDataRef(this->markovMatrixB_70);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_01_markovMatrixA_69 = this->gen_01_markovMatrixA_69->allocateIfNeeded();

    if (this->markovMatrixA_69->hasRequestedSize()) {
        if (this->markovMatrixA_69->wantsFill())
            this->zeroDataRef(this->markovMatrixA_69);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->gen_01_trimEnds_68 = this->gen_01_trimEnds_68->allocateIfNeeded();

    if (this->trimEnds_68->hasRequestedSize()) {
        if (this->trimEnds_68->wantsFill())
            this->zeroDataRef(this->trimEnds_68);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->gen_01_trimStarts_67 = this->gen_01_trimStarts_67->allocateIfNeeded();

    if (this->trimStarts_67->hasRequestedSize()) {
        if (this->trimStarts_67->wantsFill())
            this->zeroDataRef(this->trimStarts_67);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->gen_01_grainLevels_66 = this->gen_01_grainLevels_66->allocateIfNeeded();

    if (this->grainLevels_66->hasRequestedSize()) {
        if (this->grainLevels_66->wantsFill())
            this->zeroDataRef(this->grainLevels_66);

        this->getEngine()->sendDataRefUpdated(4);
    }

    this->gen_01_captureActive_65 = this->gen_01_captureActive_65->allocateIfNeeded();

    if (this->captureActive_65->hasRequestedSize()) {
        if (this->captureActive_65->wantsFill())
            this->zeroDataRef(this->captureActive_65);

        this->getEngine()->sendDataRefUpdated(5);
    }

    this->gen_01_capturePositions_64 = this->gen_01_capturePositions_64->allocateIfNeeded();

    if (this->capturePositions_64->hasRequestedSize()) {
        if (this->capturePositions_64->wantsFill())
            this->zeroDataRef(this->capturePositions_64);

        this->getEngine()->sendDataRefUpdated(6);
    }

    this->gen_01_grainQueue_63 = this->gen_01_grainQueue_63->allocateIfNeeded();

    if (this->grainQueue_63->hasRequestedSize()) {
        if (this->grainQueue_63->wantsFill())
            this->zeroDataRef(this->grainQueue_63);

        this->getEngine()->sendDataRefUpdated(7);
    }

    this->gen_01_poolR_62 = this->gen_01_poolR_62->allocateIfNeeded();

    if (this->poolR_62->hasRequestedSize()) {
        if (this->poolR_62->wantsFill())
            this->zeroDataRef(this->poolR_62);

        this->getEngine()->sendDataRefUpdated(8);
    }

    this->gen_01_poolL_61 = this->gen_01_poolL_61->allocateIfNeeded();

    if (this->poolL_61->hasRequestedSize()) {
        if (this->poolL_61->wantsFill())
            this->zeroDataRef(this->poolL_61);

        this->getEngine()->sendDataRefUpdated(9);
    }

    this->gen_01_feedbackR_75_buffer = this->gen_01_feedbackR_75_buffer->allocateIfNeeded();

    if (this->gen_01_feedbackR_75_bufferobj->hasRequestedSize()) {
        if (this->gen_01_feedbackR_75_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_feedbackR_75_bufferobj);

        this->getEngine()->sendDataRefUpdated(10);
    }

    this->gen_01_feedbackL_74_buffer = this->gen_01_feedbackL_74_buffer->allocateIfNeeded();

    if (this->gen_01_feedbackL_74_bufferobj->hasRequestedSize()) {
        if (this->gen_01_feedbackL_74_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_feedbackL_74_bufferobj);

        this->getEngine()->sendDataRefUpdated(11);
    }

    this->gen_01_triggerDelay_73_buffer = this->gen_01_triggerDelay_73_buffer->allocateIfNeeded();

    if (this->gen_01_triggerDelay_73_bufferobj->hasRequestedSize()) {
        if (this->gen_01_triggerDelay_73_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_triggerDelay_73_bufferobj);

        this->getEngine()->sendDataRefUpdated(12);
    }

    this->gen_01_preR_72_buffer = this->gen_01_preR_72_buffer->allocateIfNeeded();

    if (this->gen_01_preR_72_bufferobj->hasRequestedSize()) {
        if (this->gen_01_preR_72_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_preR_72_bufferobj);

        this->getEngine()->sendDataRefUpdated(13);
    }

    this->gen_01_preL_71_buffer = this->gen_01_preL_71_buffer->allocateIfNeeded();

    if (this->gen_01_preL_71_bufferobj->hasRequestedSize()) {
        if (this->gen_01_preL_71_bufferobj->wantsFill())
            this->zeroDataRef(this->gen_01_preL_71_bufferobj);

        this->getEngine()->sendDataRefUpdated(14);
    }
}

void initializeObjects() {
    this->gen_01_feedbackAge_197_init();
    this->gen_01_loopDelayFade_196_init();
    this->gen_01_previousLoopDelaySamples_195_init();
    this->gen_01_loopDelaySamples_194_init();
    this->gen_01_auditionStart_193_init();
    this->gen_01_auditionLevel_192_init();
    this->gen_01_auditionAttack_191_init();
    this->gen_01_auditionBody_190_init();
    this->gen_01_auditionPosition_189_init();
    this->gen_01_auditionSlot_188_init();
    this->gen_01_pendingReorderTo_187_init();
    this->gen_01_pendingReorderFrom_186_init();
    this->gen_01_pendingReorder_185_init();
    this->gen_01_previousReorderCommit_184_init();
    this->gen_01_previousAuditionRequest_183_init();
    this->gen_01_previousRemoveRequest_182_init();
    this->gen_01_grainStartSchedule_181_init();
    this->gen_01_previousDelayedGate_180_init();
    this->gen_01_transportRunSamples_179_init();
    this->gen_01_timingPhaseReady_178_init();
    this->gen_01_previousTimingPhase_177_init();
    this->gen_01_visualStep_176_init();
    this->gen_01_visualCountdown_175_init();
    this->gen_01_visualSlot_174_init();
    this->gen_01_previousClear_173_init();
    this->gen_01_clearFlushRemaining_172_init();
    this->gen_01_clearCountdown_171_init();
    this->gen_01_lastSamplesPerBeat_170_init();
    this->gen_01_previousHostRunning_169_init();
    this->gen_01_stealPan_168_init();
    this->gen_01_stealFadePosition_167_init();
    this->gen_01_stealInitialGain_166_init();
    this->gen_01_stealDirection_165_init();
    this->gen_01_stealPosition_164_init();
    this->gen_01_stealSlot_163_init();
    this->gen_01_randomState_162_init();
    this->gen_01_voiceStart7_161_init();
    this->gen_01_voiceStart6_160_init();
    this->gen_01_voiceStart5_159_init();
    this->gen_01_voiceStart4_158_init();
    this->gen_01_voiceStart3_157_init();
    this->gen_01_voiceStart2_156_init();
    this->gen_01_voiceStart1_155_init();
    this->gen_01_voiceStart0_154_init();
    this->gen_01_voicePan7_153_init();
    this->gen_01_voicePan6_152_init();
    this->gen_01_voicePan5_151_init();
    this->gen_01_voicePan4_150_init();
    this->gen_01_voicePan3_149_init();
    this->gen_01_voicePan2_148_init();
    this->gen_01_voicePan1_147_init();
    this->gen_01_voicePan0_146_init();
    this->gen_01_voiceReverse7_145_init();
    this->gen_01_voiceLevel7_144_init();
    this->gen_01_voiceAttack7_143_init();
    this->gen_01_voiceBody7_142_init();
    this->gen_01_voicePos7_141_init();
    this->gen_01_voiceSlot7_140_init();
    this->gen_01_voiceReverse6_139_init();
    this->gen_01_voiceLevel6_138_init();
    this->gen_01_voiceAttack6_137_init();
    this->gen_01_voiceBody6_136_init();
    this->gen_01_voicePos6_135_init();
    this->gen_01_voiceSlot6_134_init();
    this->gen_01_voiceReverse5_133_init();
    this->gen_01_voiceLevel5_132_init();
    this->gen_01_voiceAttack5_131_init();
    this->gen_01_voiceBody5_130_init();
    this->gen_01_voicePos5_129_init();
    this->gen_01_voiceSlot5_128_init();
    this->gen_01_voiceReverse4_127_init();
    this->gen_01_voiceLevel4_126_init();
    this->gen_01_voiceAttack4_125_init();
    this->gen_01_voiceBody4_124_init();
    this->gen_01_voicePos4_123_init();
    this->gen_01_voiceSlot4_122_init();
    this->gen_01_voiceReverse3_121_init();
    this->gen_01_voiceLevel3_120_init();
    this->gen_01_voiceAttack3_119_init();
    this->gen_01_voiceBody3_118_init();
    this->gen_01_voicePos3_117_init();
    this->gen_01_voiceSlot3_116_init();
    this->gen_01_voiceReverse2_115_init();
    this->gen_01_voiceLevel2_114_init();
    this->gen_01_voiceAttack2_113_init();
    this->gen_01_voiceBody2_112_init();
    this->gen_01_voicePos2_111_init();
    this->gen_01_voiceSlot2_110_init();
    this->gen_01_voiceReverse1_109_init();
    this->gen_01_voiceLevel1_108_init();
    this->gen_01_voiceAttack1_107_init();
    this->gen_01_voiceBody1_106_init();
    this->gen_01_voicePos1_105_init();
    this->gen_01_voiceSlot1_104_init();
    this->gen_01_voiceReverse0_103_init();
    this->gen_01_voiceLevel0_102_init();
    this->gen_01_voiceAttack0_101_init();
    this->gen_01_voiceBody0_100_init();
    this->gen_01_voicePos0_99_init();
    this->gen_01_voiceSlot0_98_init();
    this->gen_01_nextVoice_97_init();
    this->gen_01_deferNewest_96_init();
    this->gen_01_rotationRandomState_95_init();
    this->gen_01_rotationBeatPhase_94_init();
    this->gen_01_rotationOffset_93_init();
    this->gen_01_markovActiveBank_92_init();
    this->gen_01_previousMarkovCommit_91_init();
    this->gen_01_previousSelectionMode_90_init();
    this->gen_01_grainRandomState_89_init();
    this->gen_01_grainCursor_88_init();
    this->gen_01_stepIndex_87_init();
    this->gen_01_clockPhase_86_init();
    this->gen_01_poolCount_85_init();
    this->gen_01_captureSlot_84_init();
    this->gen_01_rearmCounter_83_init();
    this->gen_01_onsetArmed_82_init();
    this->gen_01_cooldown_81_init();
    this->gen_01_adaptiveThreshold_80_init();
    this->gen_01_activityEnv_79_init();
    this->gen_01_levelEnv_78_init();
    this->gen_01_slowEnv_77_init();
    this->gen_01_fastEnv_76_init();
    this->gen_01_feedbackR_75_init();
    this->gen_01_feedbackL_74_init();
    this->gen_01_triggerDelay_73_init();
    this->gen_01_preR_72_init();
    this->gen_01_preL_71_init();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void extractState(PatcherStateInterface& ) {}

void applyState() {}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    {
        this->scheduleParamInit(14, 0);
    }

    {
        this->scheduleParamInit(15, 0);
    }

    {
        this->scheduleParamInit(16, 0);
    }

    {
        this->scheduleParamInit(17, 0);
    }

    {
        this->scheduleParamInit(18, 0);
    }

    {
        this->scheduleParamInit(19, 0);
    }

    {
        this->scheduleParamInit(20, 0);
    }

    {
        this->scheduleParamInit(21, 0);
    }

    {
        this->scheduleParamInit(22, 0);
    }

    {
        this->scheduleParamInit(23, 0);
    }

    {
        this->scheduleParamInit(24, 0);
    }

    {
        this->scheduleParamInit(25, 0);
    }

    {
        this->scheduleParamInit(26, 0);
    }

    {
        this->scheduleParamInit(27, 0);
    }

    {
        this->scheduleParamInit(28, 0);
    }

    {
        this->scheduleParamInit(29, 0);
    }

    {
        this->scheduleParamInit(30, 0);
    }

    {
        this->scheduleParamInit(31, 0);
    }

    {
        this->scheduleParamInit(32, 0);
    }

    {
        this->scheduleParamInit(33, 0);
    }

    {
        this->scheduleParamInit(34, 0);
    }

    {
        this->scheduleParamInit(35, 0);
    }

    {
        this->scheduleParamInit(36, 0);
    }

    {
        this->scheduleParamInit(37, 0);
    }

    {
        this->scheduleParamInit(38, 0);
    }

    {
        this->scheduleParamInit(39, 0);
    }

    {
        this->scheduleParamInit(40, 0);
    }

    {
        this->scheduleParamInit(41, 0);
    }

    {
        this->scheduleParamInit(42, 0);
    }

    {
        this->scheduleParamInit(43, 0);
    }

    this->processParamInitEvents();
}

number gen_01_param_ScatterloomDSP_sensitivity_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_sensitivity_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_sensitivity_set(number v) {
    v = this->gen_01_sensitivity_constrain(v);
    this->gen_01_sensitivity = v;
}

number gen_01_param_ScatterloomDSP_autoSensitivity_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_autoSensitivity_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_autoSensitivity_set(number v) {
    v = this->gen_01_autoSensitivity_constrain(v);
    this->gen_01_autoSensitivity = v;
}

number gen_01_param_ScatterloomDSP_captureOn_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_captureOn_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_captureOn_set(number v) {
    v = this->gen_01_captureOn_constrain(v);
    this->gen_01_captureOn = v;
}

number gen_01_param_ScatterloomDSP_grain_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_grain_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grain_set(number v) {
    v = this->gen_01_grain_constrain(v);
    this->gen_01_grain = v;
}

number gen_01_param_ScatterloomDSP_attack_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_attack_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_attack_set(number v) {
    v = this->gen_01_attack_constrain(v);
    this->gen_01_attack = v;
}

number gen_01_param_ScatterloomDSP_grainCount_value_constrain(number v) const {
    v = (v > 9 ? 9 : (v < 1 ? 1 : v));
    return v;
}

number gen_01_grainCount_constrain(number v) const {
    if (v < 1)
        v = 1;

    if (v > 9)
        v = 9;

    return v;
}

void gen_01_grainCount_set(number v) {
    v = this->gen_01_grainCount_constrain(v);
    this->gen_01_grainCount = v;
}

number gen_01_param_ScatterloomDSP_steps_value_constrain(number v) const {
    v = (v > 32 ? 32 : (v < 1 ? 1 : v));
    return v;
}

number gen_01_steps_constrain(number v) const {
    if (v < 1)
        v = 1;

    if (v > 32)
        v = 32;

    return v;
}

void gen_01_steps_set(number v) {
    v = this->gen_01_steps_constrain(v);
    this->gen_01_steps = v;
}

number gen_01_param_ScatterloomDSP_pulses_value_constrain(number v) const {
    v = (v > 32 ? 32 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_pulses_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 32)
        v = 32;

    return v;
}

void gen_01_pulses_set(number v) {
    v = this->gen_01_pulses_constrain(v);
    this->gen_01_pulses = v;
}

number gen_01_param_ScatterloomDSP_rotation_value_constrain(number v) const {
    v = (v > 31 ? 31 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_rotation_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 31)
        v = 31;

    return v;
}

void gen_01_rotation_set(number v) {
    v = this->gen_01_rotation_constrain(v);
    this->gen_01_rotation = v;
}

number gen_01_param_ScatterloomDSP_feedback_value_constrain(number v) const {
    v = (v > 1.15 ? 1.15 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_feedback_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1.15)
        v = 1.15;

    return v;
}

void gen_01_feedback_set(number v) {
    v = this->gen_01_feedback_constrain(v);
    this->gen_01_feedback = v;
}

number gen_01_param_ScatterloomDSP_mixAmount_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_mixAmount_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_mixAmount_set(number v) {
    v = this->gen_01_mixAmount_constrain(v);
    this->gen_01_mixAmount = v;
}

number gen_01_param_ScatterloomDSP_grainFeedback_value_constrain(number v) const {
    v = (v > 1.15 ? 1.15 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_grainFeedback_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1.15)
        v = 1.15;

    return v;
}

void gen_01_grainFeedback_set(number v) {
    v = this->gen_01_grainFeedback_constrain(v);
    this->gen_01_grainFeedback = v;
}

number gen_01_param_ScatterloomDSP_reverseProbability_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_reverseProbability_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_reverseProbability_set(number v) {
    v = this->gen_01_reverseProbability_constrain(v);
    this->gen_01_reverseProbability = v;
}

number gen_01_param_ScatterloomDSP_clearPool_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_clearPool_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_clearPool_set(number v) {
    v = this->gen_01_clearPool_constrain(v);
    this->gen_01_clearPool = v;
}

number gen_01_param_ScatterloomDSP_division_value_constrain(number v) const {
    v = (v > 13 ? 13 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_division_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 13)
        v = 13;

    return v;
}

void gen_01_division_set(number v) {
    v = this->gen_01_division_constrain(v);
    this->gen_01_division = v;
}

number gen_01_param_ScatterloomDSP_rotationInterval_value_constrain(number v) const {
    v = (v > 13 ? 13 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_rotationInterval_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 13)
        v = 13;

    return v;
}

void gen_01_rotationInterval_set(number v) {
    v = this->gen_01_rotationInterval_constrain(v);
    this->gen_01_rotationInterval = v;
}

number gen_01_param_ScatterloomDSP_grainPan0_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan0_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan0_set(number v) {
    v = this->gen_01_grainPan0_constrain(v);
    this->gen_01_grainPan0 = v;
}

number gen_01_param_ScatterloomDSP_grainPan1_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan1_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan1_set(number v) {
    v = this->gen_01_grainPan1_constrain(v);
    this->gen_01_grainPan1 = v;
}

number gen_01_param_ScatterloomDSP_grainPan2_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan2_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan2_set(number v) {
    v = this->gen_01_grainPan2_constrain(v);
    this->gen_01_grainPan2 = v;
}

number gen_01_param_ScatterloomDSP_grainPan3_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan3_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan3_set(number v) {
    v = this->gen_01_grainPan3_constrain(v);
    this->gen_01_grainPan3 = v;
}

number gen_01_param_ScatterloomDSP_grainPan4_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan4_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan4_set(number v) {
    v = this->gen_01_grainPan4_constrain(v);
    this->gen_01_grainPan4 = v;
}

number gen_01_param_ScatterloomDSP_grainPan5_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan5_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan5_set(number v) {
    v = this->gen_01_grainPan5_constrain(v);
    this->gen_01_grainPan5 = v;
}

number gen_01_param_ScatterloomDSP_grainPan6_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan6_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan6_set(number v) {
    v = this->gen_01_grainPan6_constrain(v);
    this->gen_01_grainPan6 = v;
}

number gen_01_param_ScatterloomDSP_grainPan7_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan7_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan7_set(number v) {
    v = this->gen_01_grainPan7_constrain(v);
    this->gen_01_grainPan7 = v;
}

number gen_01_param_ScatterloomDSP_grainPan8_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < -1 ? -1 : v));
    return v;
}

number gen_01_grainPan8_constrain(number v) const {
    if (v < -1)
        v = -1;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_grainPan8_set(number v) {
    v = this->gen_01_grainPan8_constrain(v);
    this->gen_01_grainPan8 = v;
}

number gen_01_param_ScatterloomDSP_grainSelectionMode_value_constrain(number v) const {
    v = (v > 2 ? 2 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_grainSelectionMode_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 2)
        v = 2;

    return v;
}

void gen_01_grainSelectionMode_set(number v) {
    v = this->gen_01_grainSelectionMode_constrain(v);
    this->gen_01_grainSelectionMode = v;
}

number gen_01_param_ScatterloomDSP_loopDivision_value_constrain(number v) const {
    v = (v > 13 ? 13 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_loopDivision_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 13)
        v = 13;

    return v;
}

void gen_01_loopDivision_set(number v) {
    v = this->gen_01_loopDivision_constrain(v);
    this->gen_01_loopDivision = v;
}

number gen_01_param_ScatterloomDSP_timingOffset_value_constrain(number v) const {
    v = (v > 0.2 ? 0.2 : (v < -0.2 ? -0.2 : v));
    return v;
}

number gen_01_timingOffset_constrain(number v) const {
    if (v < -0.2)
        v = -0.2;

    if (v > 0.2)
        v = 0.2;

    return v;
}

void gen_01_timingOffset_set(number v) {
    v = this->gen_01_timingOffset_constrain(v);
    this->gen_01_timingOffset = v;
}

number gen_01_param_ScatterloomDSP_removeGrain_value_constrain(number v) const {
    v = (v > 9 ? 9 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_removeGrain_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 9)
        v = 9;

    return v;
}

void gen_01_removeGrain_set(number v) {
    v = this->gen_01_removeGrain_constrain(v);
    this->gen_01_removeGrain = v;
}

number gen_01_param_ScatterloomDSP_auditionGrain_value_constrain(number v) const {
    v = (v > 9 ? 9 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_auditionGrain_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 9)
        v = 9;

    return v;
}

void gen_01_auditionGrain_set(number v) {
    v = this->gen_01_auditionGrain_constrain(v);
    this->gen_01_auditionGrain = v;
}

number gen_01_param_ScatterloomDSP_reorderFrom_value_constrain(number v) const {
    v = (v > 9 ? 9 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_reorderFrom_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 9)
        v = 9;

    return v;
}

void gen_01_reorderFrom_set(number v) {
    v = this->gen_01_reorderFrom_constrain(v);
    this->gen_01_reorderFrom = v;
}

number gen_01_param_ScatterloomDSP_reorderTo_value_constrain(number v) const {
    v = (v > 9 ? 9 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_reorderTo_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 9)
        v = 9;

    return v;
}

void gen_01_reorderTo_set(number v) {
    v = this->gen_01_reorderTo_constrain(v);
    this->gen_01_reorderTo = v;
}

number gen_01_param_ScatterloomDSP_reorderCommit_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_reorderCommit_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_reorderCommit_set(number v) {
    v = this->gen_01_reorderCommit_constrain(v);
    this->gen_01_reorderCommit = v;
}

number gen_01_param_ScatterloomDSP_markovWeight0_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight0_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight0_set(number v) {
    v = this->gen_01_markovWeight0_constrain(v);
    this->gen_01_markovWeight0 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight1_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight1_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight1_set(number v) {
    v = this->gen_01_markovWeight1_constrain(v);
    this->gen_01_markovWeight1 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight2_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight2_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight2_set(number v) {
    v = this->gen_01_markovWeight2_constrain(v);
    this->gen_01_markovWeight2 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight3_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight3_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight3_set(number v) {
    v = this->gen_01_markovWeight3_constrain(v);
    this->gen_01_markovWeight3 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight4_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight4_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight4_set(number v) {
    v = this->gen_01_markovWeight4_constrain(v);
    this->gen_01_markovWeight4 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight5_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight5_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight5_set(number v) {
    v = this->gen_01_markovWeight5_constrain(v);
    this->gen_01_markovWeight5 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight6_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight6_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight6_set(number v) {
    v = this->gen_01_markovWeight6_constrain(v);
    this->gen_01_markovWeight6 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight7_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight7_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight7_set(number v) {
    v = this->gen_01_markovWeight7_constrain(v);
    this->gen_01_markovWeight7 = v;
}

number gen_01_param_ScatterloomDSP_markovWeight8_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovWeight8_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovWeight8_set(number v) {
    v = this->gen_01_markovWeight8_constrain(v);
    this->gen_01_markovWeight8 = v;
}

number gen_01_param_ScatterloomDSP_markovEditRow_value_constrain(number v) const {
    v = (v > 8 ? 8 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovEditRow_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 8)
        v = 8;

    return v;
}

void gen_01_markovEditRow_set(number v) {
    v = this->gen_01_markovEditRow_constrain(v);
    this->gen_01_markovEditRow = v;
}

number gen_01_param_ScatterloomDSP_markovCommit_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

number gen_01_markovCommit_constrain(number v) const {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_markovCommit_set(number v) {
    v = this->gen_01_markovCommit_constrain(v);
    this->gen_01_markovCommit = v;
}

void transport_01_outtempo_set(number ) {}

void gen_01_in3_set(number v) {
    this->gen_01_in3 = v;
}

void transport_01_state_set(number v) {
    this->gen_01_in3_set(v);
}

template<typename LISTTYPE> void transport_01_outtimesig_set(const LISTTYPE& ) {}

void beatstosamps_tilde_01_perform(number beattime, SampleValue * out1, Index n) {
    RNBO_UNUSED(beattime);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = this->safediv(1 * 60 * this->sr, this->tempo());
    }
}

void gen_01_perform(
    const Sample * in1,
    const Sample * in2,
    number in3,
    const Sample * in4,
    number in5,
    number sensitivity,
    number autoSensitivity,
    number captureOn,
    number grain,
    number attack,
    number grainCount,
    number steps,
    number pulses,
    number rotation,
    number feedback,
    number mixAmount,
    number grainFeedback,
    number reverseProbability,
    number clearPool,
    number division,
    number rotationInterval,
    number grainPan0,
    number grainPan1,
    number grainPan2,
    number grainPan3,
    number grainPan4,
    number grainPan5,
    number grainPan6,
    number grainPan7,
    number grainPan8,
    number grainSelectionMode,
    number loopDivision,
    number timingOffset,
    number removeGrain,
    number auditionGrain,
    number reorderFrom,
    number reorderTo,
    number reorderCommit,
    number markovWeight0,
    number markovWeight1,
    number markovWeight2,
    number markovWeight3,
    number markovWeight4,
    number markovWeight5,
    number markovWeight6,
    number markovWeight7,
    number markovWeight8,
    number markovEditRow,
    number markovCommit,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    SampleValue * out5,
    SampleValue * out6,
    SampleValue * out7,
    SampleValue * out8,
    SampleValue * out9,
    SampleValue * out10,
    SampleValue * out11,
    SampleValue * out12,
    Index n
) {
    RNBO_UNUSED(in5);
    auto __gen_01_feedbackAge_197_value = this->gen_01_feedbackAge_197_value;
    auto __gen_01_previousLoopDelaySamples_195_value = this->gen_01_previousLoopDelaySamples_195_value;
    auto __gen_01_loopDelayFade_196_value = this->gen_01_loopDelayFade_196_value;
    auto __gen_01_loopDelaySamples_194_value = this->gen_01_loopDelaySamples_194_value;
    auto __gen_01_stealFadePosition_167_value = this->gen_01_stealFadePosition_167_value;
    auto __gen_01_stealInitialGain_166_value = this->gen_01_stealInitialGain_166_value;
    auto __gen_01_stealPan_168_value = this->gen_01_stealPan_168_value;
    auto __gen_01_stealDirection_165_value = this->gen_01_stealDirection_165_value;
    auto __gen_01_stealPosition_164_value = this->gen_01_stealPosition_164_value;
    auto __gen_01_stealSlot_163_value = this->gen_01_stealSlot_163_value;
    auto __gen_01_voiceStart7_161_value = this->gen_01_voiceStart7_161_value;
    auto __gen_01_voiceStart6_160_value = this->gen_01_voiceStart6_160_value;
    auto __gen_01_voiceStart5_159_value = this->gen_01_voiceStart5_159_value;
    auto __gen_01_voiceStart4_158_value = this->gen_01_voiceStart4_158_value;
    auto __gen_01_voiceStart3_157_value = this->gen_01_voiceStart3_157_value;
    auto __gen_01_voiceStart2_156_value = this->gen_01_voiceStart2_156_value;
    auto __gen_01_voiceStart1_155_value = this->gen_01_voiceStart1_155_value;
    auto __gen_01_voiceStart0_154_value = this->gen_01_voiceStart0_154_value;
    auto __gen_01_voicePan7_153_value = this->gen_01_voicePan7_153_value;
    auto __gen_01_voicePan6_152_value = this->gen_01_voicePan6_152_value;
    auto __gen_01_voicePan5_151_value = this->gen_01_voicePan5_151_value;
    auto __gen_01_voicePan4_150_value = this->gen_01_voicePan4_150_value;
    auto __gen_01_voicePan3_149_value = this->gen_01_voicePan3_149_value;
    auto __gen_01_voicePan2_148_value = this->gen_01_voicePan2_148_value;
    auto __gen_01_voicePan1_147_value = this->gen_01_voicePan1_147_value;
    auto __gen_01_voicePan0_146_value = this->gen_01_voicePan0_146_value;
    auto __gen_01_voiceReverse7_145_value = this->gen_01_voiceReverse7_145_value;
    auto __gen_01_voiceReverse6_139_value = this->gen_01_voiceReverse6_139_value;
    auto __gen_01_voiceReverse5_133_value = this->gen_01_voiceReverse5_133_value;
    auto __gen_01_voiceReverse4_127_value = this->gen_01_voiceReverse4_127_value;
    auto __gen_01_voiceReverse3_121_value = this->gen_01_voiceReverse3_121_value;
    auto __gen_01_voiceReverse2_115_value = this->gen_01_voiceReverse2_115_value;
    auto __gen_01_voiceReverse1_109_value = this->gen_01_voiceReverse1_109_value;
    auto __gen_01_voiceReverse0_103_value = this->gen_01_voiceReverse0_103_value;
    auto __gen_01_voiceSlot7_140_value = this->gen_01_voiceSlot7_140_value;
    auto __gen_01_voiceSlot6_134_value = this->gen_01_voiceSlot6_134_value;
    auto __gen_01_voiceSlot5_128_value = this->gen_01_voiceSlot5_128_value;
    auto __gen_01_voiceSlot4_122_value = this->gen_01_voiceSlot4_122_value;
    auto __gen_01_voiceSlot3_116_value = this->gen_01_voiceSlot3_116_value;
    auto __gen_01_voiceSlot2_110_value = this->gen_01_voiceSlot2_110_value;
    auto __gen_01_voiceSlot1_104_value = this->gen_01_voiceSlot1_104_value;
    auto __gen_01_voiceSlot0_98_value = this->gen_01_voiceSlot0_98_value;
    auto __gen_01_nextVoice_97_value = this->gen_01_nextVoice_97_value;
    auto __gen_01_voicePos7_141_value = this->gen_01_voicePos7_141_value;
    auto __gen_01_voiceBody7_142_value = this->gen_01_voiceBody7_142_value;
    auto __gen_01_voiceAttack7_143_value = this->gen_01_voiceAttack7_143_value;
    auto __gen_01_voiceLevel7_144_value = this->gen_01_voiceLevel7_144_value;
    auto __gen_01_voicePos6_135_value = this->gen_01_voicePos6_135_value;
    auto __gen_01_voiceBody6_136_value = this->gen_01_voiceBody6_136_value;
    auto __gen_01_voiceAttack6_137_value = this->gen_01_voiceAttack6_137_value;
    auto __gen_01_voiceLevel6_138_value = this->gen_01_voiceLevel6_138_value;
    auto __gen_01_voicePos5_129_value = this->gen_01_voicePos5_129_value;
    auto __gen_01_voiceBody5_130_value = this->gen_01_voiceBody5_130_value;
    auto __gen_01_voiceAttack5_131_value = this->gen_01_voiceAttack5_131_value;
    auto __gen_01_voiceLevel5_132_value = this->gen_01_voiceLevel5_132_value;
    auto __gen_01_voicePos4_123_value = this->gen_01_voicePos4_123_value;
    auto __gen_01_voiceBody4_124_value = this->gen_01_voiceBody4_124_value;
    auto __gen_01_voiceAttack4_125_value = this->gen_01_voiceAttack4_125_value;
    auto __gen_01_voiceLevel4_126_value = this->gen_01_voiceLevel4_126_value;
    auto __gen_01_voicePos3_117_value = this->gen_01_voicePos3_117_value;
    auto __gen_01_voiceBody3_118_value = this->gen_01_voiceBody3_118_value;
    auto __gen_01_voiceAttack3_119_value = this->gen_01_voiceAttack3_119_value;
    auto __gen_01_voiceLevel3_120_value = this->gen_01_voiceLevel3_120_value;
    auto __gen_01_voicePos2_111_value = this->gen_01_voicePos2_111_value;
    auto __gen_01_voiceBody2_112_value = this->gen_01_voiceBody2_112_value;
    auto __gen_01_voiceAttack2_113_value = this->gen_01_voiceAttack2_113_value;
    auto __gen_01_voiceLevel2_114_value = this->gen_01_voiceLevel2_114_value;
    auto __gen_01_voicePos1_105_value = this->gen_01_voicePos1_105_value;
    auto __gen_01_voiceBody1_106_value = this->gen_01_voiceBody1_106_value;
    auto __gen_01_voiceAttack1_107_value = this->gen_01_voiceAttack1_107_value;
    auto __gen_01_voiceLevel1_108_value = this->gen_01_voiceLevel1_108_value;
    auto __gen_01_voicePos0_99_value = this->gen_01_voicePos0_99_value;
    auto __gen_01_voiceBody0_100_value = this->gen_01_voiceBody0_100_value;
    auto __gen_01_voiceAttack0_101_value = this->gen_01_voiceAttack0_101_value;
    auto __gen_01_voiceLevel0_102_value = this->gen_01_voiceLevel0_102_value;
    auto __gen_01_randomState_162_value = this->gen_01_randomState_162_value;
    auto __gen_01_auditionStart_193_value = this->gen_01_auditionStart_193_value;
    auto __gen_01_auditionLevel_192_value = this->gen_01_auditionLevel_192_value;
    auto __gen_01_auditionAttack_191_value = this->gen_01_auditionAttack_191_value;
    auto __gen_01_auditionBody_190_value = this->gen_01_auditionBody_190_value;
    auto __gen_01_auditionPosition_189_value = this->gen_01_auditionPosition_189_value;
    auto __gen_01_auditionSlot_188_value = this->gen_01_auditionSlot_188_value;
    auto __gen_01_visualSlot_174_value = this->gen_01_visualSlot_174_value;
    auto __gen_01_visualCountdown_175_value = this->gen_01_visualCountdown_175_value;
    auto __gen_01_markovActiveBank_92_value = this->gen_01_markovActiveBank_92_value;
    auto __gen_01_previousMarkovCommit_91_value = this->gen_01_previousMarkovCommit_91_value;
    auto __gen_01_grainRandomState_89_value = this->gen_01_grainRandomState_89_value;
    auto __gen_01_deferNewest_96_value = this->gen_01_deferNewest_96_value;
    auto __gen_01_grainCursor_88_value = this->gen_01_grainCursor_88_value;
    auto __gen_01_previousSelectionMode_90_value = this->gen_01_previousSelectionMode_90_value;
    auto __gen_01_visualStep_176_value = this->gen_01_visualStep_176_value;
    auto __gen_01_previousTimingPhase_177_value = this->gen_01_previousTimingPhase_177_value;
    auto __gen_01_timingPhaseReady_178_value = this->gen_01_timingPhaseReady_178_value;
    auto __gen_01_previousDelayedGate_180_value = this->gen_01_previousDelayedGate_180_value;
    auto __gen_01_transportRunSamples_179_value = this->gen_01_transportRunSamples_179_value;
    auto __gen_01_grainStartSchedule_181_value = this->gen_01_grainStartSchedule_181_value;
    auto __gen_01_stepIndex_87_value = this->gen_01_stepIndex_87_value;
    auto __gen_01_rotationOffset_93_value = this->gen_01_rotationOffset_93_value;
    auto __gen_01_rotationRandomState_95_value = this->gen_01_rotationRandomState_95_value;
    auto __gen_01_rotationBeatPhase_94_value = this->gen_01_rotationBeatPhase_94_value;
    auto __gen_01_clockPhase_86_value = this->gen_01_clockPhase_86_value;
    auto __gen_01_previousHostRunning_169_value = this->gen_01_previousHostRunning_169_value;
    auto __gen_01_lastSamplesPerBeat_170_value = this->gen_01_lastSamplesPerBeat_170_value;
    auto __gen_01_pendingReorderTo_187_value = this->gen_01_pendingReorderTo_187_value;
    auto __gen_01_pendingReorderFrom_186_value = this->gen_01_pendingReorderFrom_186_value;
    auto __gen_01_pendingReorder_185_value = this->gen_01_pendingReorder_185_value;
    auto __gen_01_poolCount_85_value = this->gen_01_poolCount_85_value;
    auto __gen_01_previousReorderCommit_184_value = this->gen_01_previousReorderCommit_184_value;
    auto __gen_01_previousAuditionRequest_183_value = this->gen_01_previousAuditionRequest_183_value;
    auto __gen_01_previousRemoveRequest_182_value = this->gen_01_previousRemoveRequest_182_value;
    auto __gen_01_captureSlot_84_value = this->gen_01_captureSlot_84_value;
    auto __gen_01_rearmCounter_83_value = this->gen_01_rearmCounter_83_value;
    auto __gen_01_onsetArmed_82_value = this->gen_01_onsetArmed_82_value;
    auto __gen_01_cooldown_81_value = this->gen_01_cooldown_81_value;
    auto __gen_01_clearFlushRemaining_172_value = this->gen_01_clearFlushRemaining_172_value;
    auto __gen_01_clearCountdown_171_value = this->gen_01_clearCountdown_171_value;
    auto __gen_01_previousClear_173_value = this->gen_01_previousClear_173_value;
    auto __gen_01_adaptiveThreshold_80_value = this->gen_01_adaptiveThreshold_80_value;
    auto __gen_01_activityEnv_79_value = this->gen_01_activityEnv_79_value;
    auto __gen_01_levelEnv_78_value = this->gen_01_levelEnv_78_value;
    auto __gen_01_slowEnv_77_value = this->gen_01_slowEnv_77_value;
    auto __gen_01_fastEnv_76_value = this->gen_01_fastEnv_76_value;
    // SCATTERLOOM_POOL_COMMAND_BRIDGE: apply prepared imports/restores once per block.
    ::scatterloomApplyPendingPoolCommand(
        [this](int index, float left, float right) { this->poke_default(this->gen_01_poolL_61, left, index, 0, 0); this->poke_default(this->gen_01_poolR_62, right, index, 0, 0); },
        [this](int position, int slot) { this->poke_default(this->gen_01_grainQueue_63, slot, position, 0, 0); },
        [this](int slot, double isActive, double position, double level) { this->poke_default(this->gen_01_captureActive_65, isActive, slot, 0, 0); this->poke_default(this->gen_01_capturePositions_64, position, slot, 0, 0); this->poke_default(this->gen_01_grainLevels_66, level, slot, 0, 0); },
        [this](int slot, int start, int end) { this->poke_default(this->gen_01_trimStarts_67, start, slot, 0, 0); this->poke_default(this->gen_01_trimEnds_68, end, slot, 0, 0); },
        __gen_01_poolCount_85_value, __gen_01_captureSlot_84_value);

    Index i;

    for (i = 0; i < (Index)n; i++) {
        number ScatterloomDSP_12 = 0;
        number ScatterloomDSP_11 = 0;
        number ScatterloomDSP_10 = 0;
        number ScatterloomDSP_9 = 0;
        number ScatterloomDSP_8 = 0;
        number ScatterloomDSP_7 = 0;
        number ScatterloomDSP_6 = 0;
        number ScatterloomDSP_5 = 0;
        number ScatterloomDSP_4 = 0;
        number ScatterloomDSP_3 = 0;
        number ScatterloomDSP_2 = 0;
        number ScatterloomDSP_1 = 0;
        number ScatterloomDSP_0 = 0;

        {
            auto markovCommit_60 = markovCommit;
            auto markovEditRow_59 = markovEditRow;
            auto markovWeight8_58 = markovWeight8;
            auto markovWeight7_57 = markovWeight7;
            auto markovWeight6_56 = markovWeight6;
            auto markovWeight5_55 = markovWeight5;
            auto markovWeight4_54 = markovWeight4;
            auto markovWeight3_53 = markovWeight3;
            auto markovWeight2_52 = markovWeight2;
            auto markovWeight1_51 = markovWeight1;
            auto markovWeight0_50 = markovWeight0;
            auto reorderCommit_49 = reorderCommit;
            auto reorderTo_48 = reorderTo;
            auto reorderFrom_47 = reorderFrom;
            auto auditionGrain_46 = auditionGrain;
            auto removeGrain_45 = removeGrain;
            auto timingOffset_44 = timingOffset;
            auto loopDivision_43 = loopDivision;
            auto grainSelectionMode_42 = grainSelectionMode;
            auto grainPan8_41 = grainPan8;
            auto grainPan7_40 = grainPan7;
            auto grainPan6_39 = grainPan6;
            auto grainPan5_38 = grainPan5;
            auto grainPan4_37 = grainPan4;
            auto grainPan3_36 = grainPan3;
            auto grainPan2_35 = grainPan2;
            auto grainPan1_34 = grainPan1;
            auto grainPan0_33 = grainPan0;
            auto rotationInterval_32 = rotationInterval;
            auto division_31 = division;
            auto clearPool_30 = clearPool;
            auto reverseProbability_29 = reverseProbability;
            auto grainFeedback_28 = grainFeedback;
            auto mixAmount_27 = mixAmount;
            auto feedback_26 = feedback;
            auto rotation_25 = rotation;
            auto pulses_24 = pulses;
            auto steps_23 = steps;
            auto grainCount_22 = grainCount;
            auto attack_21 = attack;
            auto grain_20 = grain;
            auto captureOn_19 = captureOn;
            auto autoSensitivity_18 = autoSensitivity;
            auto sensitivity_17 = sensitivity;
            auto hostSamplesPerBeat_16 = in4[(Index)i];
            auto hostRunning_15 = in3;
            auto inputR_14 = in2[(Index)i];
            auto inputL_13 = in1[(Index)i];
            number sens_199 = this->gen_01_slide_198_next(sensitivity_17, 1600, 1600);
            number grainNorm_201 = this->gen_01_slide_200_next(grain_20, 2200, 2200);
            number attackNorm_203 = this->gen_01_slide_202_next(attack_21, 1200, 1200);
            number timingOffsetNorm_205 = this->gen_01_slide_204_next(timingOffset_44, 1200, 1200);
            number fb_207 = this->gen_01_slide_206_next(feedback_26, 3000, 3000);
            number grainFb_209 = this->gen_01_slide_208_next(grainFeedback_28, 1200, 1200);
            number reverseProb_211 = this->gen_01_slide_210_next(reverseProbability_29, 1200, 1200);
            number wet_213 = this->gen_01_slide_212_next(mixAmount_27, 1200, 1200);
            number slotSize_214 = 262144;
            auto captureLength_215 = this->minimum(slotSize_214, this->sr * 2.05);
            auto defaultTrimEnd_216 = this->minimum(slotSize_214 - 2, this->sr * 2);
            number captureIsOn_217 = captureOn_19 >= 0.5;
            auto detector_218 = this->maximum(rnbo_abs(inputL_13), rnbo_abs(inputR_14));
            __gen_01_fastEnv_76_value = __gen_01_fastEnv_76_value + (detector_218 - __gen_01_fastEnv_76_value) * 0.08;
            __gen_01_slowEnv_77_value = __gen_01_slowEnv_77_value + (detector_218 - __gen_01_slowEnv_77_value) * 0.001;
            __gen_01_levelEnv_78_value = ((bool)(captureIsOn_217) ? __gen_01_levelEnv_78_value + (detector_218 - __gen_01_levelEnv_78_value) * 0.00005 : __gen_01_levelEnv_78_value);
            auto rise_219 = this->maximum(0, __gen_01_fastEnv_76_value - __gen_01_slowEnv_77_value);
            __gen_01_activityEnv_79_value = ((bool)(captureIsOn_217) ? __gen_01_activityEnv_79_value + ((this->maximum(1, this->sr * 0.25) == 0. ? 0. : (rise_219 - __gen_01_activityEnv_79_value) / this->maximum(1, this->sr * 0.25))) : __gen_01_activityEnv_79_value);
            number manualThreshold_220 = 0.12 + sens_199 * (0.003 - 0.12);

            number autoTarget_221 = this->__wrapped_op_clamp(
                this->maximum(__gen_01_levelEnv_78_value * 0.16, __gen_01_activityEnv_79_value * 3),
                0.006,
                0.1
            );

            number autoAdaptRate_222 = (autoTarget_221 > __gen_01_adaptiveThreshold_80_value ? 0.002 : (this->maximum(1, this->sr * 8) == 0. ? 0. : (number)1 / this->maximum(1, this->sr * 8)));
            number inputIsActive_223 = captureIsOn_217 * (__gen_01_levelEnv_78_value > 0.001);
            __gen_01_adaptiveThreshold_80_value = ((bool)(inputIsActive_223) ? __gen_01_adaptiveThreshold_80_value + (autoTarget_221 - __gen_01_adaptiveThreshold_80_value) * autoAdaptRate_222 : __gen_01_adaptiveThreshold_80_value);
            number autoThreshold_224 = __gen_01_adaptiveThreshold_80_value;
            number threshold_225 = (autoSensitivity_18 >= 0.5 ? autoThreshold_224 : manualThreshold_220);
            number effectiveSensitivity_226 = (autoSensitivity_18 >= 0.5 ? ((0.12 - autoThreshold_224) / (number)0.117 > 1 ? 1 : ((0.12 - autoThreshold_224) / (number)0.117 < 0 ? 0 : (0.12 - autoThreshold_224) / (number)0.117)) : sens_199);
            number hostIsRunning_227 = hostRunning_15 >= 0.5;
            number clearRequest_228 = clearPool_30 >= 0.5;
            number clearEdge_229 = clearRequest_228 * (__gen_01_previousClear_173_value < 0.5);
            __gen_01_previousClear_173_value = clearRequest_228;
            auto clearFadeLength_230 = this->maximum(1, this->sr);
            auto clearFlushLength_231 = this->minimum(262142, this->sr * 0.5);
            number nextClearCountdown_232 = ((bool)(clearEdge_229) ? clearFadeLength_230 : this->maximum(0, __gen_01_clearCountdown_171_value - 1));
            number resetNow_233 = (__gen_01_clearCountdown_171_value > 0) * (nextClearCountdown_232 <= 0);
            number nextClearFlush_234 = ((bool)(resetNow_233) ? clearFlushLength_231 : this->maximum(0, __gen_01_clearFlushRemaining_172_value - 1));
            __gen_01_clearCountdown_171_value = nextClearCountdown_232;
            __gen_01_clearFlushRemaining_172_value = nextClearFlush_234;
            number clearActive_235 = (nextClearCountdown_232 > 0) + (nextClearFlush_234 > 0);
            number clearGain_236 = (nextClearCountdown_232 > 0 ? (clearFadeLength_230 == 0. ? 0. : nextClearCountdown_232 / clearFadeLength_230) : (nextClearFlush_234 > 0 ? 0 : 1));
            number manualCaptureEnabled_237 = sensitivity_17 > 0.00001;
            number detectorModeEnabled_238 = (autoSensitivity_18 >= 0.5) + manualCaptureEnabled_237 > 0;
            number captureEnabled_239 = (clearActive_235 == 0) * detectorModeEnabled_238 * (captureOn_19 >= 0.5);
            number aboveThreshold_240 = rise_219 > threshold_225;
            number belowRearmThreshold_241 = rise_219 < threshold_225 * 0.25;
            number detectedOnset_242 = aboveThreshold_240 * (__gen_01_cooldown_81_value <= 0) * __gen_01_onsetArmed_82_value * detectorModeEnabled_238;
            number onset_243 = detectedOnset_242 * captureEnabled_239;
            number settledSamples_244 = this->sr * 0.025;
            __gen_01_rearmCounter_83_value = ((bool)(detectedOnset_242) ? 0 : ((bool)(belowRearmThreshold_241) ? this->minimum(settledSamples_244, __gen_01_rearmCounter_83_value + 1) : 0));
            __gen_01_onsetArmed_82_value = ((bool)(detectedOnset_242) ? 0 : ((__gen_01_rearmCounter_83_value >= settledSamples_244) * (__gen_01_cooldown_81_value <= 0) ? 1 : __gen_01_onsetArmed_82_value));
            __gen_01_cooldown_81_value = ((bool)(detectedOnset_242) ? this->sr * 0.12 : this->maximum(0, __gen_01_cooldown_81_value - 1));
            auto preRollSamples_245 = this->minimum(8190, this->sr * 0.02);
            number captureL_246 = this->gen_01_preL_71_read(preRollSamples_245, 0);
            number captureR_247 = this->gen_01_preR_72_read(preRollSamples_245, 0);
            this->gen_01_preL_71_write(inputL_13);
            this->gen_01_preR_72_write(inputR_14);
            number newSlot_248 = __gen_01_captureSlot_84_value;
            number removeRequest_249 = this->__wrapped_op_clamp(rnbo_floor(removeGrain_45 + 0.5), 0, 9);
            number removeEdge_250 = (removeRequest_249 > 0) * (__gen_01_previousRemoveRequest_182_value == 0);
            __gen_01_previousRemoveRequest_182_value = ((bool)(resetNow_233) ? 0 : removeRequest_249);
            number auditionRequest_251 = this->__wrapped_op_clamp(rnbo_floor(auditionGrain_46 + 0.5), 0, 9);
            number auditionEdge_252 = (auditionRequest_251 > 0) * (__gen_01_previousAuditionRequest_183_value == 0);
            __gen_01_previousAuditionRequest_183_value = ((bool)(resetNow_233) ? 0 : auditionRequest_251);
            number reorderCommitHigh_253 = reorderCommit_49 >= 0.5;
            number reorderEdge_254 = reorderCommitHigh_253 * (__gen_01_previousReorderCommit_184_value == 0);
            __gen_01_previousReorderCommit_184_value = ((bool)(resetNow_233) ? 0 : reorderCommitHigh_253);
            number auditionPositionInQueue_255 = auditionRequest_251 - 1;
            number removePosition_256 = removeRequest_249 - 1;
            number reorderFromPosition_257 = this->__wrapped_op_clamp(rnbo_floor(reorderFrom_47 + 0.5) - 1, 0, 8);
            number reorderToPosition_258 = this->__wrapped_op_clamp(rnbo_floor(reorderTo_48 + 0.5) - 1, 0, 8);
            number removeValid_259 = removeEdge_250 * (removePosition_256 >= 0) * (removePosition_256 < __gen_01_poolCount_85_value) * (onset_243 == 0) * (clearActive_235 == 0);
            number reorderRequestValid_260 = reorderEdge_254 * (reorderFromPosition_257 < __gen_01_poolCount_85_value) * (reorderToPosition_258 < __gen_01_poolCount_85_value) * (reorderFromPosition_257 != reorderToPosition_258);
            auto queuedReorder_261 = this->maximum(__gen_01_pendingReorder_185_value, reorderRequestValid_260);
            number queuedReorderFrom_262 = ((bool)(reorderRequestValid_260) ? reorderFromPosition_257 : __gen_01_pendingReorderFrom_186_value);
            number queuedReorderTo_263 = ((bool)(reorderRequestValid_260) ? reorderToPosition_258 : __gen_01_pendingReorderTo_187_value);
            number reorderValid_264 = queuedReorder_261 * (queuedReorderFrom_262 < __gen_01_poolCount_85_value) * (queuedReorderTo_263 < __gen_01_poolCount_85_value) * (queuedReorderFrom_262 != queuedReorderTo_263) * (onset_243 == 0) * (removeValid_259 == 0) * (clearActive_235 == 0);
            number removedSlot = 0;

            auto result_265 = this->peek_default(
                this->gen_01_grainQueue_63,
                (removePosition_256 > 8 ? 8 : (removePosition_256 < 0 ? 0 : removePosition_256)),
                0
            );

            removedSlot = result_265[0];
            number reorderedSlot = 0;
            auto result_266 = this->peek_default(this->gen_01_grainQueue_63, queuedReorderFrom_262, 0);
            reorderedSlot = result_266[0];

            if ((bool)(resetNow_233)) {
                for (number queueIndex = 0; queueIndex < 9; queueIndex = queueIndex + 1) {
                    this->poke_default(this->gen_01_grainQueue_63, 0, queueIndex, 0, 0);
                    this->poke_default(this->gen_01_captureActive_65, 0, queueIndex, 0, 0);
                    this->poke_default(this->gen_01_grainLevels_66, 0, queueIndex, 0, 0);
                    this->poke_default(this->gen_01_trimStarts_67, 0, queueIndex, 0, 0);
                    this->poke_default(this->gen_01_trimEnds_68, 0, queueIndex, 0, 0);
                }
            } else if ((bool)(onset_243)) {
                for (number queueIndex = 8; queueIndex > 0; queueIndex = queueIndex + -1) {
                    number peek_1 = 0;
                    number peek_2 = 0;
                    auto result_267 = this->peek_default(this->gen_01_grainQueue_63, queueIndex - 1, 0);
                    peek_2 = result_267[1];
                    peek_1 = result_267[0];
                    this->poke_default(this->gen_01_grainQueue_63, peek_1, queueIndex, 0, 0);
                }

                this->poke_default(this->gen_01_grainQueue_63, newSlot_248, 0, 0, 0);
                this->poke_default(this->gen_01_capturePositions_64, 0, newSlot_248, 0, 0);
                this->poke_default(this->gen_01_captureActive_65, 1, newSlot_248, 0, 0);
                this->poke_default(this->gen_01_grainLevels_66, 1, newSlot_248, 0, 0);
                this->poke_default(this->gen_01_trimStarts_67, 0, newSlot_248, 0, 0);
                this->poke_default(this->gen_01_trimEnds_68, defaultTrimEnd_216, newSlot_248, 0, 0);
            } else if ((bool)(removeValid_259)) {
                for (number queueIndex = 0; queueIndex < 8; queueIndex = queueIndex + 1) {
                    if (queueIndex >= removePosition_256) {
                        number peek_3 = 0;
                        number peek_4 = 0;
                        auto result_268 = this->peek_default(this->gen_01_grainQueue_63, queueIndex + 1, 0);
                        peek_4 = result_268[1];
                        peek_3 = result_268[0];
                        this->poke_default(this->gen_01_grainQueue_63, peek_3, queueIndex, 0, 0);
                    }
                }

                this->poke_default(this->gen_01_grainQueue_63, 0, 8, 0, 0);
                this->poke_default(this->gen_01_captureActive_65, 0, removedSlot, 0, 0);
                this->poke_default(this->gen_01_grainLevels_66, 0, removedSlot, 0, 0);
            } else if ((bool)(reorderValid_264)) {
                if (queuedReorderFrom_262 < queuedReorderTo_263) {
                    for (number queueIndex = 0; queueIndex < 8; queueIndex = queueIndex + 1) {
                        if ((queueIndex >= queuedReorderFrom_262) * (queueIndex < queuedReorderTo_263)) {
                            number peek_5 = 0;
                            number peek_6 = 0;
                            auto result_269 = this->peek_default(this->gen_01_grainQueue_63, queueIndex + 1, 0);
                            peek_6 = result_269[1];
                            peek_5 = result_269[0];
                            this->poke_default(this->gen_01_grainQueue_63, peek_5, queueIndex, 0, 0);
                        }
                    }
                } else {
                    for (number queueIndex = 8; queueIndex > 0; queueIndex = queueIndex + -1) {
                        if ((queueIndex <= queuedReorderFrom_262) * (queueIndex > queuedReorderTo_263)) {
                            number peek_7 = 0;
                            number peek_8 = 0;
                            auto result_270 = this->peek_default(this->gen_01_grainQueue_63, queueIndex - 1, 0);
                            peek_8 = result_270[1];
                            peek_7 = result_270[0];
                            this->poke_default(this->gen_01_grainQueue_63, peek_7, queueIndex, 0, 0);
                        }
                    }
                }

                this->poke_default(this->gen_01_grainQueue_63, reorderedSlot, queuedReorderTo_263, 0, 0);
            }

            __gen_01_pendingReorder_185_value = ((bool)(resetNow_233) ? 0 : ((bool)(reorderValid_264) ? 0 : queuedReorder_261));
            __gen_01_pendingReorderFrom_186_value = ((bool)(resetNow_233) ? 0 : ((bool)(reorderRequestValid_260) ? reorderFromPosition_257 : __gen_01_pendingReorderFrom_186_value));
            __gen_01_pendingReorderTo_187_value = ((bool)(resetNow_233) ? 0 : ((bool)(reorderRequestValid_260) ? reorderToPosition_258 : __gen_01_pendingReorderTo_187_value));
            __gen_01_poolCount_85_value = ((bool)(resetNow_233) ? 0 : ((bool)(onset_243) ? this->minimum(9, __gen_01_poolCount_85_value + 1) : ((bool)(removeValid_259) ? this->maximum(0, __gen_01_poolCount_85_value - 1) : __gen_01_poolCount_85_value)));
            number queueChanged_271 = onset_243 + removeValid_259 + reorderValid_264 > 0;
            number nextCaptureSlot_272 = __gen_01_captureSlot_84_value;

            if ((bool)(queueChanged_271)) {
                if (__gen_01_poolCount_85_value >= 9) {
                    auto result_273 = this->peek_default(this->gen_01_grainQueue_63, 8, 0);
                    nextCaptureSlot_272 = result_273[0];
                } else {
                    number freeSlotFound_274 = 0;

                    for (number candidateSlot = 0; candidateSlot < 9; candidateSlot = candidateSlot + 1) {
                        number candidateInQueue_275 = 0;

                        for (number candidatePosition = 0; candidatePosition < 9; candidatePosition = candidatePosition + 1) {
                            number peek_9 = 0;
                            number peek_10 = 0;
                            auto result_276 = this->peek_default(this->gen_01_grainQueue_63, candidatePosition, 0);
                            peek_10 = result_276[1];
                            peek_9 = result_276[0];

                            candidateInQueue_275 = this->maximum(
                                candidateInQueue_275,
                                (candidatePosition < __gen_01_poolCount_85_value) * (peek_9 == candidateSlot)
                            );
                        }

                        if ((freeSlotFound_274 == 0) * (candidateInQueue_275 == 0)) {
                            nextCaptureSlot_272 = candidateSlot;
                            freeSlotFound_274 = 1;
                        }
                    }
                }
            }

            __gen_01_captureSlot_84_value = ((bool)(resetNow_233) ? 0 : nextCaptureSlot_272);

            if (onset_243 > 0.5) ::scatterloomBeginWaveformCapture((int)newSlot_248);
            if (removeValid_259 > 0.5) ::scatterloomRemoveWaveform((int)removePosition_256);
            if (resetNow_233 > 0.5) ::scatterloomClearWaveforms();
            if (reorderValid_264 > 0.5) ::scatterloomConfirmReorder((int)queuedReorderFrom_262, (int)queuedReorderTo_263); // SCATTERLOOM_REORDER_CONFIRM
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            unsigned mpcRecordingSlots = 0;
#endif
            for (number captureIndex = 0; captureIndex < 9; captureIndex = captureIndex + 1) {
                number peek_11 = 0;
                number peek_12 = 0;
                auto result_277 = this->peek_default(this->gen_01_captureActive_65, captureIndex, 0);
                peek_12 = result_277[1];
                peek_11 = result_277[0];
                number captureIsActive_278 = peek_11 > 0.5;
                number activeCapturePosition = 0;
                auto result_279 = this->peek_default(this->gen_01_capturePositions_64, captureIndex, 0);
                activeCapturePosition = result_279[0];

                if ((bool)(captureIsActive_278)) {
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
                    mpcRecordingSlots |= 1u << static_cast<unsigned>(captureIndex);
#endif
                    ::scatterloomAccumulateWaveform((int)captureIndex, activeCapturePosition, captureLength_215, captureL_246, captureR_247);
                    number activeCapturePoolIndex_280 = captureIndex * slotSize_214 + ((activeCapturePosition > slotSize_214 - 1 ? slotSize_214 - 1 : (activeCapturePosition < 0 ? 0 : activeCapturePosition)));
                    this->poke_default(this->gen_01_poolL_61, captureL_246, activeCapturePoolIndex_280, 0, 0);
                    this->poke_default(this->gen_01_poolR_62, captureR_247, activeCapturePoolIndex_280, 0, 0);
                    auto nextCapturePosition_281 = this->minimum(captureLength_215, activeCapturePosition + 1);

                    this->poke_default(
                        this->gen_01_capturePositions_64,
                        nextCapturePosition_281,
                        captureIndex,
                        0,
                        0
                    );

                    if (nextCapturePosition_281 >= captureLength_215) {
                        this->poke_default(this->gen_01_captureActive_65, 0, captureIndex, 0, 0);
                    }
                }
            }

            number safeSteps_282 = this->__wrapped_op_clamp(rnbo_floor(steps_23 + 0.5), 1, 32);
            number safePulses_283 = this->__wrapped_op_clamp(rnbo_floor(pulses_24 + 0.5), 0, safeSteps_282);
            number safeRotation_284 = this->__wrapped_op_clamp(rnbo_floor(rotation_25 + 0.5), 0, 31);
            number divisionIndex_285 = this->__wrapped_op_clamp(rnbo_floor(division_31 + 0.5), 0, 13);
            number DivisionStepsPerBeat_286 = 0;

            {
                auto divisionIndex_287 = divisionIndex_285;
                DivisionStepsPerBeat_286 = (divisionIndex_287 == 0 ? 0.125 : (divisionIndex_287 == 1 ? 0.25 : (divisionIndex_287 == 2 ? 0.5 : (divisionIndex_287 == 3 ? 0.75 : (divisionIndex_287 == 4 ? 1 : (divisionIndex_287 == 5 ? 1.5 : (divisionIndex_287 == 6 ? (number)2 / (number)3 : (divisionIndex_287 == 7 ? 2 : (divisionIndex_287 == 8 ? 3 : (divisionIndex_287 == 9 ? (number)4 / (number)3 : (divisionIndex_287 == 10 ? 4 : (divisionIndex_287 == 11 ? 6 : (divisionIndex_287 == 12 ? (number)8 / (number)3 : 8)))))))))))));
            }

            number stepsPerBeat_288 = DivisionStepsPerBeat_286;
            number minimumSamplesPerBeat_289 = this->sr * 60 / (number)240;
            number maximumSamplesPerBeat_290 = this->sr * 60 / (number)30;
            number hostTempoValid_291 = (hostSamplesPerBeat_16 >= minimumSamplesPerBeat_289) * (hostSamplesPerBeat_16 <= maximumSamplesPerBeat_290);
            __gen_01_lastSamplesPerBeat_170_value = ((bool)(hostTempoValid_291) ? hostSamplesPerBeat_16 : __gen_01_lastSamplesPerBeat_170_value);
            number safeSamplesPerBeat_292 = (__gen_01_lastSamplesPerBeat_170_value > maximumSamplesPerBeat_290 ? maximumSamplesPerBeat_290 : (__gen_01_lastSamplesPerBeat_170_value < minimumSamplesPerBeat_289 ? minimumSamplesPerBeat_289 : __gen_01_lastSamplesPerBeat_170_value));
            number loopDivisionIndex_293 = this->__wrapped_op_clamp(rnbo_floor(loopDivision_43 + 0.5), 0, 13);
            number DivisionStepsPerBeat_294 = 0;

            {
                auto divisionIndex_295 = loopDivisionIndex_293;
                DivisionStepsPerBeat_294 = (divisionIndex_295 == 0 ? 0.125 : (divisionIndex_295 == 1 ? 0.25 : (divisionIndex_295 == 2 ? 0.5 : (divisionIndex_295 == 3 ? 0.75 : (divisionIndex_295 == 4 ? 1 : (divisionIndex_295 == 5 ? 1.5 : (divisionIndex_295 == 6 ? (number)2 / (number)3 : (divisionIndex_295 == 7 ? 2 : (divisionIndex_295 == 8 ? 3 : (divisionIndex_295 == 9 ? (number)4 / (number)3 : (divisionIndex_295 == 10 ? 4 : (divisionIndex_295 == 11 ? 6 : (divisionIndex_295 == 12 ? (number)8 / (number)3 : 8)))))))))))));
            }

            number loopStepsPerBeat_296 = DivisionStepsPerBeat_294;
            number desiredLoopDelaySamples_297 = (((loopStepsPerBeat_296 == 0. ? 0. : safeSamplesPerBeat_292 / loopStepsPerBeat_296)) > 4194302 ? 4194302 : (((loopStepsPerBeat_296 == 0. ? 0. : safeSamplesPerBeat_292 / loopStepsPerBeat_296)) < 16 ? 16 : (loopStepsPerBeat_296 == 0. ? 0. : safeSamplesPerBeat_292 / loopStepsPerBeat_296)));

            auto syncedStepSamples_298 = this->maximum(
                1,
                (stepsPerBeat_288 == 0. ? 0. : safeSamplesPerBeat_292 / stepsPerBeat_288)
            );

            number stepSamples_299 = syncedStepSamples_298;
            number hostStarted_300 = hostIsRunning_227 * (__gen_01_previousHostRunning_169_value < 0.5);
            number hostStopped_301 = (hostIsRunning_227 < 0.5) * (__gen_01_previousHostRunning_169_value >= 0.5);
            number clockEnabled_302 = hostIsRunning_227;
            number nextClock_303 = __gen_01_clockPhase_86_value + ((this->maximum(1, stepSamples_299) == 0. ? 0. : clockEnabled_302 / this->maximum(1, stepSamples_299)));
            number stepClockTrig_304 = clockEnabled_302 * (nextClock_303 >= 1);
            __gen_01_clockPhase_86_value = (hostStarted_300 + hostStopped_301 > 0 ? 0 : ((bool)(stepClockTrig_304) ? nextClock_303 - 1 : nextClock_303));
            __gen_01_previousHostRunning_169_value = hostIsRunning_227;
            number clockTrig_305 = ((bool)(hostStarted_300) ? 1 : stepClockTrig_304);
            number rotationIntervalIndex_306 = this->__wrapped_op_clamp(rnbo_floor(rotationInterval_32 + 0.5), 0, 13);
            number rotationBeats_307 = (rotationIntervalIndex_306 == 1 ? 1 : (rotationIntervalIndex_306 == 2 ? 2 : (rotationIntervalIndex_306 == 3 ? 3 : (rotationIntervalIndex_306 == 4 ? 4 : (rotationIntervalIndex_306 == 5 ? 6 : (rotationIntervalIndex_306 == 6 ? 8 : (rotationIntervalIndex_306 == 7 ? 12 : (rotationIntervalIndex_306 == 8 ? 16 : (rotationIntervalIndex_306 == 9 ? 24 : (rotationIntervalIndex_306 == 10 ? 32 : (rotationIntervalIndex_306 == 11 ? 48 : (rotationIntervalIndex_306 == 12 ? 64 : 96))))))))))));
            number rotationEnabled_308 = rotationIntervalIndex_306 > 0;
            number rotationSamplesPerBeat_309 = safeSamplesPerBeat_292;
            number nextRotationBeatPhase_310 = __gen_01_rotationBeatPhase_94_value + ((this->maximum(1, rotationSamplesPerBeat_309) == 0. ? 0. : clockEnabled_302 / this->maximum(1, rotationSamplesPerBeat_309)));
            number rotationClockTrig_311 = rotationEnabled_308 * clockEnabled_302 * (nextRotationBeatPhase_310 >= rotationBeats_307);
            __gen_01_rotationBeatPhase_94_value = ((bool)(hostStarted_300) ? 0 : ((bool)(rotationClockTrig_311) ? nextRotationBeatPhase_310 - rotationBeats_307 : nextRotationBeatPhase_310));
            number rotationModTrig_312 = rotationClockTrig_311;
            number nextRotationRandom_313 = fract(__gen_01_rotationRandomState_95_value * 3.971 + 0.314159);
            number randomRotationCandidate_314 = rnbo_floor(nextRotationRandom_313 * this->maximum(1, safeSteps_282 - 1));
            number nextRotationOffset_315 = (safeSteps_282 > 1 ? (randomRotationCandidate_314 >= __gen_01_rotationOffset_93_value ? randomRotationCandidate_314 + 1 : randomRotationCandidate_314) : 0);
            __gen_01_rotationRandomState_95_value = ((bool)(rotationModTrig_312) ? nextRotationRandom_313 : __gen_01_rotationRandomState_95_value);
            __gen_01_rotationOffset_93_value = (rotationEnabled_308 == 0 || (bool)(hostStarted_300) ? 0 : ((bool)(rotationModTrig_312) ? nextRotationOffset_315 : __gen_01_rotationOffset_93_value));
            number effectiveRotation_316 = this->safemod(safeRotation_284 + __gen_01_rotationOffset_93_value, safeSteps_282);
            number sequencerStep_317 = ((bool)(hostStarted_300) ? 0 : __gen_01_stepIndex_87_value);
            number rotatedStep_318 = this->safemod(sequencerStep_317 + effectiveRotation_316, safeSteps_282);
            number EuclideanStepHit_319 = 0;

            {
                auto steps_322 = safeSteps_282;
                auto pulses_321 = safePulses_283;
                auto step_320 = rotatedStep_318;
                EuclideanStepHit_319 = this->safemod(step_320 * pulses_321, steps_322) < pulses_321;
            }

            number hit_323 = clockTrig_305 * EuclideanStepHit_319;
            __gen_01_grainStartSchedule_181_value = ((bool)(clockTrig_305) ? timingOffsetNorm_205 : __gen_01_grainStartSchedule_181_value);
            number playbackTimingOffset_324 = -__gen_01_grainStartSchedule_181_value;
            number positiveOffsetSamples_325 = this->__wrapped_op_clamp(this->maximum(0, playbackTimingOffset_324) * this->sr, 1, 524286);
            this->gen_01_triggerDelay_73_write(hit_323);
            __gen_01_transportRunSamples_179_value = ((bool)(hostStarted_300) ? 1 : ((bool)(clockEnabled_302) ? __gen_01_transportRunSamples_179_value + 1 : 0));
            number delayedHitReady_326 = __gen_01_transportRunSamples_179_value >= positiveOffsetSamples_325;
            number delayedSignal_327 = this->gen_01_triggerDelay_73_read(positiveOffsetSamples_325, 0) * delayedHitReady_326;
            number delayedGate_328 = delayedSignal_327 > 0.000001;
            number delayedHit_329 = delayedGate_328 * (__gen_01_previousDelayedGate_180_value == 0);
            __gen_01_previousDelayedGate_180_value = ((bool)(resetNow_233) ? 0 : delayedGate_328);

            auto advanceSteps_330 = this->maximum(
                0,
                (this->maximum(1, stepSamples_299) == 0. ? 0. : -playbackTimingOffset_324 * this->sr / this->maximum(1, stepSamples_299))
            );

            number advanceWholeSteps_331 = rnbo_floor(advanceSteps_330);
            number advanceFraction_332 = advanceSteps_330 - advanceWholeSteps_331;
            number shiftedTimingPhase_333 = this->safemod(__gen_01_clockPhase_86_value + advanceFraction_332, 1);
            number shiftedTimingWrap_334 = __gen_01_timingPhaseReady_178_value * (shiftedTimingPhase_333 < __gen_01_previousTimingPhase_177_value);
            number fractionalAdvance_335 = advanceFraction_332 > 0.000001;
            number earlyClockTrig_336 = ((bool)(hostStarted_300) ? 1 : ((bool)(fractionalAdvance_335) ? shiftedTimingWrap_334 : clockTrig_305));
            number futureAdvance_337 = ((bool)(hostStarted_300) ? 0 : advanceWholeSteps_331);
            number futureStep_338 = this->safemod(sequencerStep_317 + futureAdvance_337, safeSteps_282);
            number futureRotatedStep_339 = this->safemod(futureStep_338 + effectiveRotation_316, safeSteps_282);
            number EuclideanStepHit_340 = 0;

            {
                auto steps_343 = safeSteps_282;
                auto pulses_342 = safePulses_283;
                auto step_341 = futureRotatedStep_339;
                EuclideanStepHit_340 = this->safemod(step_341 * pulses_342, steps_343) < pulses_342;
            }

            number earlyHit_344 = earlyClockTrig_336 * EuclideanStepHit_340;
            __gen_01_previousTimingPhase_177_value = shiftedTimingPhase_333;
            __gen_01_timingPhaseReady_178_value = 1;
            number playbackHit_345 = (playbackTimingOffset_324 < -0.000001 ? earlyHit_344 : (playbackTimingOffset_324 > 0.000001 ? delayedHit_329 : hit_323));
            __gen_01_visualStep_176_value = ((bool)(clockTrig_305) ? rotatedStep_318 : __gen_01_visualStep_176_value);
            __gen_01_stepIndex_87_value = ((bool)(clockTrig_305) ? this->safemod(sequencerStep_317 + 1, safeSteps_282) : __gen_01_stepIndex_87_value);
            number requestedGrains_346 = this->__wrapped_op_clamp(rnbo_floor(grainCount_22 + 0.5), 1, 9);
            auto availableGrains_347 = this->maximum(1, this->minimum(requestedGrains_346, __gen_01_poolCount_85_value));
            number selectionMode_348 = this->__wrapped_op_clamp(rnbo_floor(grainSelectionMode_42 + 0.5), 0, 2);
            number enteredPlayedMode_349 = (selectionMode_348 == 0) * (__gen_01_previousSelectionMode_90_value != 0);
            number useRandomGrains_350 = selectionMode_348 == 1;
            number useMarkovGrains_351 = selectionMode_348 == 2;
            number canUseOlder_352 = (__gen_01_poolCount_85_value > 1) * (requestedGrains_346 > 1);
            number orderedTransportReset_353 = (hostStarted_300 + hostStopped_301 + enteredPlayedMode_349 > 0) * (useRandomGrains_350 == 0);
            number playbackCursor_354 = ((bool)(orderedTransportReset_353) ? availableGrains_347 - 1 : __gen_01_grainCursor_88_value);
            number deferredCursor_355 = (__gen_01_deferNewest_96_value * canUseOlder_352 * useRandomGrains_350 ? 1 : playbackCursor_354);
            number nextGrainRandom_356 = fract(__gen_01_grainRandomState_89_value * 3.963 + 0.246813);
            number randomGrainCandidate_357 = rnbo_floor(nextGrainRandom_356 * this->maximum(1, availableGrains_347 - 1));
            number nextRandomCursor_358 = (availableGrains_347 > 1 ? (randomGrainCandidate_357 >= deferredCursor_355 ? randomGrainCandidate_357 + 1 : randomGrainCandidate_357) : 0);
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            // MPC-only selection bridge: matrix is supplied by the wrapper.
            number nextMarkovCursor_406 = playbackCursor_354;
            if (useMarkovGrains_351 && playbackHit_345 && scatterloomActiveBridge) {
                nextMarkovCursor_406 = scatterloomActiveBridge->markov.chooseNext(
                    static_cast<int>(playbackCursor_354),
                    static_cast<int>(availableGrains_347),
                    static_cast<float>(nextGrainRandom_356));
            }

#else
            number markovCommitHigh_359 = markovCommit_60 >= 0.5;
            number markovCommitEdge_360 = markovCommitHigh_359 * (__gen_01_previousMarkovCommit_91_value == 0);
            number markovStagingBank_361 = 1 - __gen_01_markovActiveBank_92_value;
            number markovStagingRow_362 = this->__wrapped_op_clamp(rnbo_floor(markovEditRow_59 + 0.5), 0, 8);
            number markovStagingBase_363 = markovStagingRow_362 * 9;

            if ((bool)(markovCommitEdge_360)) {
                for (number markovColumn = 0; markovColumn < 9; markovColumn = markovColumn + 1) {
                    number MarkovWeightAt_364 = 0;

                    {
                        auto weight8_374 = markovWeight8_58;
                        auto weight7_373 = markovWeight7_57;
                        auto weight6_372 = markovWeight6_56;
                        auto weight5_371 = markovWeight5_55;
                        auto weight4_370 = markovWeight4_54;
                        auto weight3_369 = markovWeight3_53;
                        auto weight2_368 = markovWeight2_52;
                        auto weight1_367 = markovWeight1_51;
                        auto weight0_366 = markovWeight0_50;
                        auto index_365 = markovColumn;
                        MarkovWeightAt_364 = (index_365 == 0 ? weight0_366 : (index_365 == 1 ? weight1_367 : (index_365 == 2 ? weight2_368 : (index_365 == 3 ? weight3_369 : (index_365 == 4 ? weight4_370 : (index_365 == 5 ? weight5_371 : (index_365 == 6 ? weight6_372 : (index_365 == 7 ? weight7_373 : weight8_374))))))));
                    }

                    auto stagedMarkovWeight_375 = this->maximum(0, MarkovWeightAt_364);

                    if (markovStagingBank_361 == 0) {
                        this->poke_default(
                            this->gen_01_markovMatrixA_69,
                            stagedMarkovWeight_375,
                            markovStagingBase_363 + markovColumn,
                            0,
                            0
                        );
                    } else {
                        this->poke_default(
                            this->gen_01_markovMatrixB_70,
                            stagedMarkovWeight_375,
                            markovStagingBase_363 + markovColumn,
                            0,
                            0
                        );
                    }
                }
            }

            __gen_01_markovActiveBank_92_value = (markovCommitEdge_360 * (markovStagingRow_362 == 8) ? markovStagingBank_361 : __gen_01_markovActiveBank_92_value);
            __gen_01_previousMarkovCommit_91_value = markovCommitHigh_359;
            number markovReadBase_376 = playbackCursor_354 * 9;
            number peek_13 = 0;
            number peek_14 = 0;
            auto result_377 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376, 0);
            peek_14 = result_377[1];
            peek_13 = result_377[0];
            number peek_15 = 0;
            number peek_16 = 0;
            auto result_378 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376, 0);
            peek_16 = result_378[1];
            peek_15 = result_378[0];
            number markovW0_379 = (availableGrains_347 > 0 ? this->maximum(0, peek_13 + __gen_01_markovActiveBank_92_value * (peek_15 - peek_13)) : 0);
            number peek_17 = 0;
            number peek_18 = 0;
            auto result_380 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 1, 0);
            peek_18 = result_380[1];
            peek_17 = result_380[0];
            number peek_19 = 0;
            number peek_20 = 0;
            auto result_381 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 1, 0);
            peek_20 = result_381[1];
            peek_19 = result_381[0];
            number markovW1_382 = (availableGrains_347 > 1 ? this->maximum(0, peek_17 + __gen_01_markovActiveBank_92_value * (peek_19 - peek_17)) : 0);
            number peek_21 = 0;
            number peek_22 = 0;
            auto result_383 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 2, 0);
            peek_22 = result_383[1];
            peek_21 = result_383[0];
            number peek_23 = 0;
            number peek_24 = 0;
            auto result_384 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 2, 0);
            peek_24 = result_384[1];
            peek_23 = result_384[0];
            number markovW2_385 = (availableGrains_347 > 2 ? this->maximum(0, peek_21 + __gen_01_markovActiveBank_92_value * (peek_23 - peek_21)) : 0);
            number peek_25 = 0;
            number peek_26 = 0;
            auto result_386 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 3, 0);
            peek_26 = result_386[1];
            peek_25 = result_386[0];
            number peek_27 = 0;
            number peek_28 = 0;
            auto result_387 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 3, 0);
            peek_28 = result_387[1];
            peek_27 = result_387[0];
            number markovW3_388 = (availableGrains_347 > 3 ? this->maximum(0, peek_25 + __gen_01_markovActiveBank_92_value * (peek_27 - peek_25)) : 0);
            number peek_29 = 0;
            number peek_30 = 0;
            auto result_389 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 4, 0);
            peek_30 = result_389[1];
            peek_29 = result_389[0];
            number peek_31 = 0;
            number peek_32 = 0;
            auto result_390 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 4, 0);
            peek_32 = result_390[1];
            peek_31 = result_390[0];
            number markovW4_391 = (availableGrains_347 > 4 ? this->maximum(0, peek_29 + __gen_01_markovActiveBank_92_value * (peek_31 - peek_29)) : 0);
            number peek_33 = 0;
            number peek_34 = 0;
            auto result_392 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 5, 0);
            peek_34 = result_392[1];
            peek_33 = result_392[0];
            number peek_35 = 0;
            number peek_36 = 0;
            auto result_393 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 5, 0);
            peek_36 = result_393[1];
            peek_35 = result_393[0];
            number markovW5_394 = (availableGrains_347 > 5 ? this->maximum(0, peek_33 + __gen_01_markovActiveBank_92_value * (peek_35 - peek_33)) : 0);
            number peek_37 = 0;
            number peek_38 = 0;
            auto result_395 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 6, 0);
            peek_38 = result_395[1];
            peek_37 = result_395[0];
            number peek_39 = 0;
            number peek_40 = 0;
            auto result_396 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 6, 0);
            peek_40 = result_396[1];
            peek_39 = result_396[0];
            number markovW6_397 = (availableGrains_347 > 6 ? this->maximum(0, peek_37 + __gen_01_markovActiveBank_92_value * (peek_39 - peek_37)) : 0);
            number peek_41 = 0;
            number peek_42 = 0;
            auto result_398 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 7, 0);
            peek_42 = result_398[1];
            peek_41 = result_398[0];
            number peek_43 = 0;
            number peek_44 = 0;
            auto result_399 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 7, 0);
            peek_44 = result_399[1];
            peek_43 = result_399[0];
            number markovW7_400 = (availableGrains_347 > 7 ? this->maximum(0, peek_41 + __gen_01_markovActiveBank_92_value * (peek_43 - peek_41)) : 0);
            number peek_45 = 0;
            number peek_46 = 0;
            auto result_401 = this->peek_default(this->gen_01_markovMatrixA_69, markovReadBase_376 + 8, 0);
            peek_46 = result_401[1];
            peek_45 = result_401[0];
            number peek_47 = 0;
            number peek_48 = 0;
            auto result_402 = this->peek_default(this->gen_01_markovMatrixB_70, markovReadBase_376 + 8, 0);
            peek_48 = result_402[1];
            peek_47 = result_402[0];
            number markovW8_403 = (availableGrains_347 > 8 ? this->maximum(0, peek_45 + __gen_01_markovActiveBank_92_value * (peek_47 - peek_45)) : 0);
            number markovTotal_404 = markovW0_379 + markovW1_382 + markovW2_385 + markovW3_388 + markovW4_391 + markovW5_394 + markovW6_397 + markovW7_400 + markovW8_403;
            number markovDraw_405 = nextGrainRandom_356 * markovTotal_404;
            number nextMarkovCursor_406 = (markovTotal_404 <= 0.000001 ? (playbackCursor_354 <= 0 ? availableGrains_347 - 1 : playbackCursor_354 - 1) : (markovDraw_405 < markovW0_379 ? 0 : (markovDraw_405 < markovW0_379 + markovW1_382 ? 1 : (markovDraw_405 < markovW0_379 + markovW1_382 + markovW2_385 ? 2 : (markovDraw_405 < markovW0_379 + markovW1_382 + markovW2_385 + markovW3_388 ? 3 : (markovDraw_405 < markovW0_379 + markovW1_382 + markovW2_385 + markovW3_388 + markovW4_391 ? 4 : (markovDraw_405 < markovW0_379 + markovW1_382 + markovW2_385 + markovW3_388 + markovW4_391 + markovW5_394 ? 5 : (markovDraw_405 < markovW0_379 + markovW1_382 + markovW2_385 + markovW3_388 + markovW4_391 + markovW5_394 + markovW6_397 ? 6 : (markovDraw_405 < markovW0_379 + markovW1_382 + markovW2_385 + markovW3_388 + markovW4_391 + markovW5_394 + markovW6_397 + markovW7_400 ? 7 : 8)))))))));
#endif
            number selectedSlot = 0;

            auto result_407 = this->peek_default(
                this->gen_01_grainQueue_63,
                (deferredCursor_355 > 8 ? 8 : (deferredCursor_355 < 0 ? 0 : deferredCursor_355)),
                0
            );

            selectedSlot = result_407[0];
            number selectedLevel = 0;

            auto result_408 = this->peek_default(
                this->gen_01_grainLevels_66,
                (selectedSlot > 8 ? 8 : (selectedSlot < 0 ? 0 : selectedSlot)),
                0
            );

            selectedLevel = result_408[0];
            number playHit_409 = playbackHit_345 * clockEnabled_302 * (1 - __gen_01_deferNewest_96_value * (1 - canUseOlder_352)) * (clearActive_235 == 0);
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            // A newly queued slot is not playable until recording has finished.
            // Otherwise the read head can enter unwritten or stale sample data.
            auto selectedCapture = this->peek_default(this->gen_01_captureActive_65, selectedSlot, 0);
            playHit_409 *= selectedCapture[0] <= 0.5;
#endif
            number auditionValid_410 = auditionEdge_252 * (auditionPositionInQueue_255 >= 0) * (auditionPositionInQueue_255 < __gen_01_poolCount_85_value) * (clearActive_235 == 0);
            number auditionSelectedSlot = 0;

            auto result_411 = this->peek_default(
                this->gen_01_grainQueue_63,
                (auditionPositionInQueue_255 > 8 ? 8 : (auditionPositionInQueue_255 < 0 ? 0 : auditionPositionInQueue_255)),
                0
            );

            auditionSelectedSlot = result_411[0];
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            // Audition obeys the same rule as sequenced grain playback.
            auto auditionCapture = this->peek_default(this->gen_01_captureActive_65, auditionSelectedSlot, 0);
            auditionValid_410 *= auditionCapture[0] <= 0.5;
#endif
            number auditionSelectedLevel = 0;

            auto result_412 = this->peek_default(
                this->gen_01_grainLevels_66,
                (auditionSelectedSlot > 8 ? 8 : (auditionSelectedSlot < 0 ? 0 : auditionSelectedSlot)),
                0
            );

            auditionSelectedLevel = result_412[0];
            number visualTrigger_413 = auditionValid_410 + playHit_409 > 0;
            number visualQueuePosition_414 = ((bool)(auditionValid_410) ? auditionRequest_251 : deferredCursor_355 + 1);
            number nextVisualCountdown_415 = ((bool)(visualTrigger_413) ? this->sr * 0.18 : this->maximum(0, __gen_01_visualCountdown_175_value - 1));
            __gen_01_visualSlot_174_value = ((bool)(visualTrigger_413) ? visualQueuePosition_414 : (nextVisualCountdown_415 > 0 ? __gen_01_visualSlot_174_value : 0));
            __gen_01_visualCountdown_175_value = nextVisualCountdown_415;
            number nextSequentialCursor_416 = (playbackCursor_354 <= 0 ? availableGrains_347 - 1 : playbackCursor_354 - 1);
            number nextGrainCursor_417 = ((bool)(useRandomGrains_350) ? nextRandomCursor_358 : ((bool)(useMarkovGrains_351) ? nextMarkovCursor_406 : nextSequentialCursor_416));
            __gen_01_grainCursor_88_value = ((bool)(resetNow_233) ? 0 : ((bool)(orderedTransportReset_353) ? ((bool)(playbackHit_345) ? nextGrainCursor_417 : playbackCursor_354) : ((bool)(onset_243) ? availableGrains_347 - 1 : (removeValid_259 + reorderValid_264 > 0 ? this->minimum(__gen_01_grainCursor_88_value, availableGrains_347 - 1) : ((bool)(playbackHit_345) ? nextGrainCursor_417 : __gen_01_grainCursor_88_value)))));
            __gen_01_grainRandomState_89_value = ((bool)(resetNow_233) ? 0.731 : (playbackHit_345 * (useRandomGrains_350 + useMarkovGrains_351 > 0) ? nextGrainRandom_356 : __gen_01_grainRandomState_89_value));
            __gen_01_previousSelectionMode_90_value = ((bool)(resetNow_233) ? 0 : selectionMode_348);
            __gen_01_deferNewest_96_value = ((bool)(resetNow_233) ? 0 : ((bool)(onset_243) ? 1 : ((bool)(playbackHit_345) ? 0 : __gen_01_deferNewest_96_value)));
            number nextSelectedLevel_418 = (selectedLevel * grainFb_209 > 2 ? 2 : (selectedLevel * grainFb_209 < 0 ? 0 : selectedLevel * grainFb_209));
            number nextSelectedLevel_49_419 = (nextSelectedLevel_418 < 0.0001 ? 0 : nextSelectedLevel_418);

            if ((bool)(playHit_409)) {
                this->poke_default(this->gen_01_grainLevels_66, nextSelectedLevel_49_419, selectedSlot, 0, 0);
            }

            auto desiredGrainSamples_420 = this->minimum(
                slotSize_214 - this->sr * 0.02,
                (0.02 + grainNorm_201 * grainNorm_201 * (2 - 0.02)) * this->sr
            );

            auto minimumAttackSamples_421 = this->minimum(desiredGrainSamples_420 * 0.5, this->sr * 0.001);

            auto desiredAttackSamples_422 = this->minimum(
                desiredGrainSamples_420,
                minimumAttackSamples_421 + attackNorm_203 * this->sr
            );

            auto voiceReleaseSamples_423 = this->maximum(16, this->sr * 0.01);
            number peek_50 = 0;
            number peek_51 = 0;
            auto result_424 = this->peek_default(this->gen_01_trimStarts_67, selectedSlot, 0);
            peek_51 = result_424[1];
            peek_50 = result_424[0];
            number selectedTrimStart_425 = (peek_50 > slotSize_214 - 18 ? slotSize_214 - 18 : (peek_50 < 0 ? 0 : peek_50));
            number peek_52 = 0;
            number peek_53 = 0;
            auto result_426 = this->peek_default(this->gen_01_trimEnds_68, selectedSlot, 0);
            peek_53 = result_426[1];
            peek_52 = result_426[0];
            number selectedTrimEnd_427 = (peek_52 > slotSize_214 - 2 ? slotSize_214 - 2 : (peek_52 < selectedTrimStart_425 + 16 ? selectedTrimStart_425 + 16 : peek_52));
            auto selectedTrimSamples_428 = this->maximum(16, selectedTrimEnd_427 - selectedTrimStart_425);

            auto selectedBodySamples_429 = this->minimum(
                desiredGrainSamples_420,
                this->maximum(1, selectedTrimSamples_428 - voiceReleaseSamples_423)
            );

            auto selectedAttackSamples_430 = this->minimum(desiredAttackSamples_422, selectedBodySamples_429);
            number peek_54 = 0;
            number peek_55 = 0;
            auto result_431 = this->peek_default(this->gen_01_trimStarts_67, auditionSelectedSlot, 0);
            peek_55 = result_431[1];
            peek_54 = result_431[0];
            number auditionTrimStart_432 = (peek_54 > slotSize_214 - 18 ? slotSize_214 - 18 : (peek_54 < 0 ? 0 : peek_54));
            number peek_56 = 0;
            number peek_57 = 0;
            auto result_433 = this->peek_default(this->gen_01_trimEnds_68, auditionSelectedSlot, 0);
            peek_57 = result_433[1];
            peek_56 = result_433[0];
            number auditionTrimEnd_434 = (peek_56 > slotSize_214 - 2 ? slotSize_214 - 2 : (peek_56 < auditionTrimStart_432 + 16 ? auditionTrimStart_432 + 16 : peek_56));
            auto auditionTrimSamples_435 = this->maximum(16, auditionTrimEnd_434 - auditionTrimStart_432);

            auto auditionBodySamples_436 = this->minimum(
                desiredGrainSamples_420,
                this->maximum(1, auditionTrimSamples_435 - voiceReleaseSamples_423)
            );

            auto auditionAttackSamples_437 = this->minimum(desiredAttackSamples_422, auditionBodySamples_436);
            number auditionReadSlot_438 = ((bool)(auditionValid_410) ? auditionSelectedSlot : __gen_01_auditionSlot_188_value);
            number auditionReadPosition_439 = ((bool)(auditionValid_410) ? 0 : __gen_01_auditionPosition_189_value);
            number auditionReadBody_440 = ((bool)(auditionValid_410) ? auditionBodySamples_436 : __gen_01_auditionBody_190_value);
            number auditionReadAttack_441 = ((bool)(auditionValid_410) ? auditionAttackSamples_437 : __gen_01_auditionAttack_191_value);
            number auditionReadLevel_442 = ((bool)(auditionValid_410) ? auditionSelectedLevel : __gen_01_auditionLevel_192_value);
            number auditionReadStart_443 = ((bool)(auditionValid_410) ? auditionTrimStart_432 : __gen_01_auditionStart_193_value);
            number auditionActive_444 = (auditionReadPosition_439 < auditionReadBody_440 + this->sr * 0.01) * (auditionReadLevel_442 > 0) * (__gen_01_poolCount_85_value > 0);
            number GrainVoiceWindow_445 = 0;

            {
                auto hasPool_450 = __gen_01_poolCount_85_value > 0;
                auto level_449 = auditionReadLevel_442;
                auto attackSamples_448 = auditionReadAttack_441;
                auto bodySamples_447 = auditionReadBody_440;
                auto position_446 = auditionReadPosition_439;
                auto releaseSamples_451 = this->maximum(16, this->sr * 0.01);
                number active_452 = (position_446 < bodySamples_447 + releaseSamples_451) * hasPool_450 * (level_449 > 0);

                number attackPhase_453 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_448) == 0. ? 0. : position_446 / this->maximum(1, attackSamples_448)),
                    0,
                    1
                );

                number releasePhase_454 = (((releaseSamples_451 == 0. ? 0. : (bodySamples_447 + releaseSamples_451 - position_446) / releaseSamples_451)) > 1 ? 1 : (((releaseSamples_451 == 0. ? 0. : (bodySamples_447 + releaseSamples_451 - position_446) / releaseSamples_451)) < 0 ? 0 : (releaseSamples_451 == 0. ? 0. : (bodySamples_447 + releaseSamples_451 - position_446) / releaseSamples_451)));
                number attackGain_455 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_453);
                number releaseGain_456 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_454);
                GrainVoiceWindow_445 = active_452 * this->minimum(attackGain_455, releaseGain_456) * level_449;
            }

            number auditionWindow_457 = GrainVoiceWindow_445;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            auditionWindow_457 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(auditionReadSlot_438))) == 0;
#endif
            number auditionIndex_458 = auditionReadSlot_438 * slotSize_214 + ((auditionReadStart_443 + auditionReadPosition_439 > slotSize_214 - 2 ? slotSize_214 - 2 : (auditionReadStart_443 + auditionReadPosition_439 < 0 ? 0 : auditionReadStart_443 + auditionReadPosition_439)));
            number peek_58 = 0;
            number peek_59 = 0;
            auto result_459 = this->peek_default(this->gen_01_poolL_61, auditionIndex_458, 0);
            peek_59 = result_459[1];
            peek_58 = result_459[0];
            number auditionL_460 = peek_58 * auditionWindow_457;
            number peek_60 = 0;
            number peek_61 = 0;
            auto result_461 = this->peek_default(this->gen_01_poolR_62, auditionIndex_458, 0);
            peek_61 = result_461[1];
            peek_60 = result_461[0];
            number auditionR_462 = peek_60 * auditionWindow_457;
            __gen_01_auditionSlot_188_value = ((bool)(resetNow_233) ? 0 : auditionReadSlot_438);
            __gen_01_auditionPosition_189_value = ((bool)(resetNow_233) ? 1048576 : auditionReadPosition_439 + auditionActive_444);
            __gen_01_auditionBody_190_value = auditionReadBody_440;
            __gen_01_auditionAttack_191_value = auditionReadAttack_441;
            __gen_01_auditionLevel_192_value = ((bool)(resetNow_233) ? 0 : auditionReadLevel_442);
            __gen_01_auditionStart_193_value = ((bool)(resetNow_233) ? 0 : auditionReadStart_443);
            number nextRandom_463 = fract(__gen_01_randomState_162_value * 3.987654 + 0.1234567);
            number reverseChoice_464 = (reverseProb_211 >= 1 ? 1 : (reverseProb_211 <= 0 ? 0 : nextRandom_463 < reverseProb_211));
            number selectedVoiceStart_465 = ((bool)(reverseChoice_464) ? selectedTrimEnd_427 - (selectedBodySamples_429 + voiceReleaseSamples_423) : selectedTrimStart_425);
            __gen_01_randomState_162_value = ((bool)(playHit_409) ? nextRandom_463 : __gen_01_randomState_162_value);
            number GrainPanAt_466 = 0;

            {
                auto pan8_476 = grainPan8_41;
                auto pan7_475 = grainPan7_40;
                auto pan6_474 = grainPan6_39;
                auto pan5_473 = grainPan5_38;
                auto pan4_472 = grainPan4_37;
                auto pan3_471 = grainPan3_36;
                auto pan2_470 = grainPan2_35;
                auto pan1_469 = grainPan1_34;
                auto pan0_468 = grainPan0_33;
                auto index_467 = selectedSlot;
                GrainPanAt_466 = (index_467 == 0 ? pan0_468 : (index_467 == 1 ? pan1_469 : (index_467 == 2 ? pan2_470 : (index_467 == 3 ? pan3_471 : (index_467 == 4 ? pan4_472 : (index_467 == 5 ? pan5_473 : (index_467 == 6 ? pan6_474 : (index_467 == 7 ? pan7_475 : pan8_476))))))));
            }

            number selectedPan_477 = (GrainPanAt_466 > 1 ? 1 : (GrainPanAt_466 < -1 ? -1 : GrainPanAt_466));
            number hasPool_478 = __gen_01_poolCount_85_value > 0;
            number GrainVoiceWindow_479 = 0;

            {
                auto hasPool_484 = hasPool_478;
                auto level_483 = __gen_01_voiceLevel0_102_value;
                auto attackSamples_482 = __gen_01_voiceAttack0_101_value;
                auto bodySamples_481 = __gen_01_voiceBody0_100_value;
                auto position_480 = __gen_01_voicePos0_99_value;
                auto releaseSamples_485 = this->maximum(16, this->sr * 0.01);
                number active_486 = (position_480 < bodySamples_481 + releaseSamples_485) * hasPool_484 * (level_483 > 0);

                number attackPhase_487 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_482) == 0. ? 0. : position_480 / this->maximum(1, attackSamples_482)),
                    0,
                    1
                );

                number releasePhase_488 = (((releaseSamples_485 == 0. ? 0. : (bodySamples_481 + releaseSamples_485 - position_480) / releaseSamples_485)) > 1 ? 1 : (((releaseSamples_485 == 0. ? 0. : (bodySamples_481 + releaseSamples_485 - position_480) / releaseSamples_485)) < 0 ? 0 : (releaseSamples_485 == 0. ? 0. : (bodySamples_481 + releaseSamples_485 - position_480) / releaseSamples_485)));
                number attackGain_489 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_487);
                number releaseGain_490 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_488);
                GrainVoiceWindow_479 = active_486 * this->minimum(attackGain_489, releaseGain_490) * level_483;
            }

            number oldWindow0_491 = GrainVoiceWindow_479;
            number GrainVoiceWindow_492 = 0;

            {
                auto hasPool_497 = hasPool_478;
                auto level_496 = __gen_01_voiceLevel1_108_value;
                auto attackSamples_495 = __gen_01_voiceAttack1_107_value;
                auto bodySamples_494 = __gen_01_voiceBody1_106_value;
                auto position_493 = __gen_01_voicePos1_105_value;
                auto releaseSamples_498 = this->maximum(16, this->sr * 0.01);
                number active_499 = (position_493 < bodySamples_494 + releaseSamples_498) * hasPool_497 * (level_496 > 0);

                number attackPhase_500 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_495) == 0. ? 0. : position_493 / this->maximum(1, attackSamples_495)),
                    0,
                    1
                );

                number releasePhase_501 = (((releaseSamples_498 == 0. ? 0. : (bodySamples_494 + releaseSamples_498 - position_493) / releaseSamples_498)) > 1 ? 1 : (((releaseSamples_498 == 0. ? 0. : (bodySamples_494 + releaseSamples_498 - position_493) / releaseSamples_498)) < 0 ? 0 : (releaseSamples_498 == 0. ? 0. : (bodySamples_494 + releaseSamples_498 - position_493) / releaseSamples_498)));
                number attackGain_502 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_500);
                number releaseGain_503 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_501);
                GrainVoiceWindow_492 = active_499 * this->minimum(attackGain_502, releaseGain_503) * level_496;
            }

            number oldWindow1_504 = GrainVoiceWindow_492;
            number GrainVoiceWindow_505 = 0;

            {
                auto hasPool_510 = hasPool_478;
                auto level_509 = __gen_01_voiceLevel2_114_value;
                auto attackSamples_508 = __gen_01_voiceAttack2_113_value;
                auto bodySamples_507 = __gen_01_voiceBody2_112_value;
                auto position_506 = __gen_01_voicePos2_111_value;
                auto releaseSamples_511 = this->maximum(16, this->sr * 0.01);
                number active_512 = (position_506 < bodySamples_507 + releaseSamples_511) * hasPool_510 * (level_509 > 0);

                number attackPhase_513 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_508) == 0. ? 0. : position_506 / this->maximum(1, attackSamples_508)),
                    0,
                    1
                );

                number releasePhase_514 = (((releaseSamples_511 == 0. ? 0. : (bodySamples_507 + releaseSamples_511 - position_506) / releaseSamples_511)) > 1 ? 1 : (((releaseSamples_511 == 0. ? 0. : (bodySamples_507 + releaseSamples_511 - position_506) / releaseSamples_511)) < 0 ? 0 : (releaseSamples_511 == 0. ? 0. : (bodySamples_507 + releaseSamples_511 - position_506) / releaseSamples_511)));
                number attackGain_515 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_513);
                number releaseGain_516 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_514);
                GrainVoiceWindow_505 = active_512 * this->minimum(attackGain_515, releaseGain_516) * level_509;
            }

            number oldWindow2_517 = GrainVoiceWindow_505;
            number GrainVoiceWindow_518 = 0;

            {
                auto hasPool_523 = hasPool_478;
                auto level_522 = __gen_01_voiceLevel3_120_value;
                auto attackSamples_521 = __gen_01_voiceAttack3_119_value;
                auto bodySamples_520 = __gen_01_voiceBody3_118_value;
                auto position_519 = __gen_01_voicePos3_117_value;
                auto releaseSamples_524 = this->maximum(16, this->sr * 0.01);
                number active_525 = (position_519 < bodySamples_520 + releaseSamples_524) * hasPool_523 * (level_522 > 0);

                number attackPhase_526 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_521) == 0. ? 0. : position_519 / this->maximum(1, attackSamples_521)),
                    0,
                    1
                );

                number releasePhase_527 = (((releaseSamples_524 == 0. ? 0. : (bodySamples_520 + releaseSamples_524 - position_519) / releaseSamples_524)) > 1 ? 1 : (((releaseSamples_524 == 0. ? 0. : (bodySamples_520 + releaseSamples_524 - position_519) / releaseSamples_524)) < 0 ? 0 : (releaseSamples_524 == 0. ? 0. : (bodySamples_520 + releaseSamples_524 - position_519) / releaseSamples_524)));
                number attackGain_528 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_526);
                number releaseGain_529 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_527);
                GrainVoiceWindow_518 = active_525 * this->minimum(attackGain_528, releaseGain_529) * level_522;
            }

            number oldWindow3_530 = GrainVoiceWindow_518;
            number GrainVoiceWindow_531 = 0;

            {
                auto hasPool_536 = hasPool_478;
                auto level_535 = __gen_01_voiceLevel4_126_value;
                auto attackSamples_534 = __gen_01_voiceAttack4_125_value;
                auto bodySamples_533 = __gen_01_voiceBody4_124_value;
                auto position_532 = __gen_01_voicePos4_123_value;
                auto releaseSamples_537 = this->maximum(16, this->sr * 0.01);
                number active_538 = (position_532 < bodySamples_533 + releaseSamples_537) * hasPool_536 * (level_535 > 0);

                number attackPhase_539 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_534) == 0. ? 0. : position_532 / this->maximum(1, attackSamples_534)),
                    0,
                    1
                );

                number releasePhase_540 = (((releaseSamples_537 == 0. ? 0. : (bodySamples_533 + releaseSamples_537 - position_532) / releaseSamples_537)) > 1 ? 1 : (((releaseSamples_537 == 0. ? 0. : (bodySamples_533 + releaseSamples_537 - position_532) / releaseSamples_537)) < 0 ? 0 : (releaseSamples_537 == 0. ? 0. : (bodySamples_533 + releaseSamples_537 - position_532) / releaseSamples_537)));
                number attackGain_541 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_539);
                number releaseGain_542 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_540);
                GrainVoiceWindow_531 = active_538 * this->minimum(attackGain_541, releaseGain_542) * level_535;
            }

            number oldWindow4_543 = GrainVoiceWindow_531;
            number GrainVoiceWindow_544 = 0;

            {
                auto hasPool_549 = hasPool_478;
                auto level_548 = __gen_01_voiceLevel5_132_value;
                auto attackSamples_547 = __gen_01_voiceAttack5_131_value;
                auto bodySamples_546 = __gen_01_voiceBody5_130_value;
                auto position_545 = __gen_01_voicePos5_129_value;
                auto releaseSamples_550 = this->maximum(16, this->sr * 0.01);
                number active_551 = (position_545 < bodySamples_546 + releaseSamples_550) * hasPool_549 * (level_548 > 0);

                number attackPhase_552 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_547) == 0. ? 0. : position_545 / this->maximum(1, attackSamples_547)),
                    0,
                    1
                );

                number releasePhase_553 = (((releaseSamples_550 == 0. ? 0. : (bodySamples_546 + releaseSamples_550 - position_545) / releaseSamples_550)) > 1 ? 1 : (((releaseSamples_550 == 0. ? 0. : (bodySamples_546 + releaseSamples_550 - position_545) / releaseSamples_550)) < 0 ? 0 : (releaseSamples_550 == 0. ? 0. : (bodySamples_546 + releaseSamples_550 - position_545) / releaseSamples_550)));
                number attackGain_554 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_552);
                number releaseGain_555 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_553);
                GrainVoiceWindow_544 = active_551 * this->minimum(attackGain_554, releaseGain_555) * level_548;
            }

            number oldWindow5_556 = GrainVoiceWindow_544;
            number GrainVoiceWindow_557 = 0;

            {
                auto hasPool_562 = hasPool_478;
                auto level_561 = __gen_01_voiceLevel6_138_value;
                auto attackSamples_560 = __gen_01_voiceAttack6_137_value;
                auto bodySamples_559 = __gen_01_voiceBody6_136_value;
                auto position_558 = __gen_01_voicePos6_135_value;
                auto releaseSamples_563 = this->maximum(16, this->sr * 0.01);
                number active_564 = (position_558 < bodySamples_559 + releaseSamples_563) * hasPool_562 * (level_561 > 0);

                number attackPhase_565 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_560) == 0. ? 0. : position_558 / this->maximum(1, attackSamples_560)),
                    0,
                    1
                );

                number releasePhase_566 = (((releaseSamples_563 == 0. ? 0. : (bodySamples_559 + releaseSamples_563 - position_558) / releaseSamples_563)) > 1 ? 1 : (((releaseSamples_563 == 0. ? 0. : (bodySamples_559 + releaseSamples_563 - position_558) / releaseSamples_563)) < 0 ? 0 : (releaseSamples_563 == 0. ? 0. : (bodySamples_559 + releaseSamples_563 - position_558) / releaseSamples_563)));
                number attackGain_567 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_565);
                number releaseGain_568 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_566);
                GrainVoiceWindow_557 = active_564 * this->minimum(attackGain_567, releaseGain_568) * level_561;
            }

            number oldWindow6_569 = GrainVoiceWindow_557;
            number GrainVoiceWindow_570 = 0;

            {
                auto hasPool_575 = hasPool_478;
                auto level_574 = __gen_01_voiceLevel7_144_value;
                auto attackSamples_573 = __gen_01_voiceAttack7_143_value;
                auto bodySamples_572 = __gen_01_voiceBody7_142_value;
                auto position_571 = __gen_01_voicePos7_141_value;
                auto releaseSamples_576 = this->maximum(16, this->sr * 0.01);
                number active_577 = (position_571 < bodySamples_572 + releaseSamples_576) * hasPool_575 * (level_574 > 0);

                number attackPhase_578 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_573) == 0. ? 0. : position_571 / this->maximum(1, attackSamples_573)),
                    0,
                    1
                );

                number releasePhase_579 = (((releaseSamples_576 == 0. ? 0. : (bodySamples_572 + releaseSamples_576 - position_571) / releaseSamples_576)) > 1 ? 1 : (((releaseSamples_576 == 0. ? 0. : (bodySamples_572 + releaseSamples_576 - position_571) / releaseSamples_576)) < 0 ? 0 : (releaseSamples_576 == 0. ? 0. : (bodySamples_572 + releaseSamples_576 - position_571) / releaseSamples_576)));
                number attackGain_580 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_578);
                number releaseGain_581 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_579);
                GrainVoiceWindow_570 = active_577 * this->minimum(attackGain_580, releaseGain_581) * level_574;
            }

            number oldWindow7_582 = GrainVoiceWindow_570;
            number stolenSlot_583 = (__gen_01_nextVoice_97_value == 0 ? __gen_01_voiceSlot0_98_value : (__gen_01_nextVoice_97_value == 1 ? __gen_01_voiceSlot1_104_value : (__gen_01_nextVoice_97_value == 2 ? __gen_01_voiceSlot2_110_value : (__gen_01_nextVoice_97_value == 3 ? __gen_01_voiceSlot3_116_value : (__gen_01_nextVoice_97_value == 4 ? __gen_01_voiceSlot4_122_value : (__gen_01_nextVoice_97_value == 5 ? __gen_01_voiceSlot5_128_value : (__gen_01_nextVoice_97_value == 6 ? __gen_01_voiceSlot6_134_value : __gen_01_voiceSlot7_140_value)))))));
            number stolenPosition_584 = (__gen_01_nextVoice_97_value == 0 ? __gen_01_voicePos0_99_value : (__gen_01_nextVoice_97_value == 1 ? __gen_01_voicePos1_105_value : (__gen_01_nextVoice_97_value == 2 ? __gen_01_voicePos2_111_value : (__gen_01_nextVoice_97_value == 3 ? __gen_01_voicePos3_117_value : (__gen_01_nextVoice_97_value == 4 ? __gen_01_voicePos4_123_value : (__gen_01_nextVoice_97_value == 5 ? __gen_01_voicePos5_129_value : (__gen_01_nextVoice_97_value == 6 ? __gen_01_voicePos6_135_value : __gen_01_voicePos7_141_value)))))));
            number stolenGain_585 = (__gen_01_nextVoice_97_value == 0 ? oldWindow0_491 : (__gen_01_nextVoice_97_value == 1 ? oldWindow1_504 : (__gen_01_nextVoice_97_value == 2 ? oldWindow2_517 : (__gen_01_nextVoice_97_value == 3 ? oldWindow3_530 : (__gen_01_nextVoice_97_value == 4 ? oldWindow4_543 : (__gen_01_nextVoice_97_value == 5 ? oldWindow5_556 : (__gen_01_nextVoice_97_value == 6 ? oldWindow6_569 : oldWindow7_582)))))));
            number stolenBody_586 = (__gen_01_nextVoice_97_value == 0 ? __gen_01_voiceBody0_100_value : (__gen_01_nextVoice_97_value == 1 ? __gen_01_voiceBody1_106_value : (__gen_01_nextVoice_97_value == 2 ? __gen_01_voiceBody2_112_value : (__gen_01_nextVoice_97_value == 3 ? __gen_01_voiceBody3_118_value : (__gen_01_nextVoice_97_value == 4 ? __gen_01_voiceBody4_124_value : (__gen_01_nextVoice_97_value == 5 ? __gen_01_voiceBody5_130_value : (__gen_01_nextVoice_97_value == 6 ? __gen_01_voiceBody6_136_value : __gen_01_voiceBody7_142_value)))))));
            number stolenReverse_587 = (__gen_01_nextVoice_97_value == 0 ? __gen_01_voiceReverse0_103_value : (__gen_01_nextVoice_97_value == 1 ? __gen_01_voiceReverse1_109_value : (__gen_01_nextVoice_97_value == 2 ? __gen_01_voiceReverse2_115_value : (__gen_01_nextVoice_97_value == 3 ? __gen_01_voiceReverse3_121_value : (__gen_01_nextVoice_97_value == 4 ? __gen_01_voiceReverse4_127_value : (__gen_01_nextVoice_97_value == 5 ? __gen_01_voiceReverse5_133_value : (__gen_01_nextVoice_97_value == 6 ? __gen_01_voiceReverse6_139_value : __gen_01_voiceReverse7_145_value)))))));
            number stolenPan_588 = (__gen_01_nextVoice_97_value == 0 ? __gen_01_voicePan0_146_value : (__gen_01_nextVoice_97_value == 1 ? __gen_01_voicePan1_147_value : (__gen_01_nextVoice_97_value == 2 ? __gen_01_voicePan2_148_value : (__gen_01_nextVoice_97_value == 3 ? __gen_01_voicePan3_149_value : (__gen_01_nextVoice_97_value == 4 ? __gen_01_voicePan4_150_value : (__gen_01_nextVoice_97_value == 5 ? __gen_01_voicePan5_151_value : (__gen_01_nextVoice_97_value == 6 ? __gen_01_voicePan6_152_value : __gen_01_voicePan7_153_value)))))));
            number stolenTrimStart_589 = (__gen_01_nextVoice_97_value == 0 ? __gen_01_voiceStart0_154_value : (__gen_01_nextVoice_97_value == 1 ? __gen_01_voiceStart1_155_value : (__gen_01_nextVoice_97_value == 2 ? __gen_01_voiceStart2_156_value : (__gen_01_nextVoice_97_value == 3 ? __gen_01_voiceStart3_157_value : (__gen_01_nextVoice_97_value == 4 ? __gen_01_voiceStart4_158_value : (__gen_01_nextVoice_97_value == 5 ? __gen_01_voiceStart5_159_value : (__gen_01_nextVoice_97_value == 6 ? __gen_01_voiceStart6_160_value : __gen_01_voiceStart7_161_value)))))));
            number stolenSamplePosition_590 = ((bool)(stolenReverse_587) ? stolenTrimStart_589 + stolenBody_586 + this->sr * 0.01 - 1 - stolenPosition_584 : stolenTrimStart_589 + stolenPosition_584);
            number assign0_591 = playHit_409 * (__gen_01_nextVoice_97_value == 0);
            number assign1_592 = playHit_409 * (__gen_01_nextVoice_97_value == 1);
            number assign2_593 = playHit_409 * (__gen_01_nextVoice_97_value == 2);
            number assign3_594 = playHit_409 * (__gen_01_nextVoice_97_value == 3);
            number assign4_595 = playHit_409 * (__gen_01_nextVoice_97_value == 4);
            number assign5_596 = playHit_409 * (__gen_01_nextVoice_97_value == 5);
            number assign6_597 = playHit_409 * (__gen_01_nextVoice_97_value == 6);
            number assign7_598 = playHit_409 * (__gen_01_nextVoice_97_value == 7);
            number readSlot0_599 = ((bool)(assign0_591) ? selectedSlot : __gen_01_voiceSlot0_98_value);
            number readPos0_600 = ((bool)(assign0_591) ? 0 : __gen_01_voicePos0_99_value);
            number readBody0_601 = ((bool)(assign0_591) ? selectedBodySamples_429 : __gen_01_voiceBody0_100_value);
            number readAttack0_602 = ((bool)(assign0_591) ? selectedAttackSamples_430 : __gen_01_voiceAttack0_101_value);
            number readLevel0_603 = ((bool)(assign0_591) ? selectedLevel : __gen_01_voiceLevel0_102_value);
            number readReverse0_604 = ((bool)(assign0_591) ? reverseChoice_464 : __gen_01_voiceReverse0_103_value);
            number readStart0_605 = ((bool)(assign0_591) ? selectedVoiceStart_465 : __gen_01_voiceStart0_154_value);
            number readPan0_606 = ((bool)(assign0_591) ? selectedPan_477 : __gen_01_voicePan0_146_value);
            number active0_607 = (readPos0_600 < readBody0_601 + this->sr * 0.01) * hasPool_478 * (readLevel0_603 > 0);
            number GrainVoiceWindow_608 = 0;

            {
                auto hasPool_613 = hasPool_478;
                auto level_612 = readLevel0_603;
                auto attackSamples_611 = readAttack0_602;
                auto bodySamples_610 = readBody0_601;
                auto position_609 = readPos0_600;
                auto releaseSamples_614 = this->maximum(16, this->sr * 0.01);
                number active_615 = (position_609 < bodySamples_610 + releaseSamples_614) * hasPool_613 * (level_612 > 0);

                number attackPhase_616 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_611) == 0. ? 0. : position_609 / this->maximum(1, attackSamples_611)),
                    0,
                    1
                );

                number releasePhase_617 = (((releaseSamples_614 == 0. ? 0. : (bodySamples_610 + releaseSamples_614 - position_609) / releaseSamples_614)) > 1 ? 1 : (((releaseSamples_614 == 0. ? 0. : (bodySamples_610 + releaseSamples_614 - position_609) / releaseSamples_614)) < 0 ? 0 : (releaseSamples_614 == 0. ? 0. : (bodySamples_610 + releaseSamples_614 - position_609) / releaseSamples_614)));
                number attackGain_618 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_616);
                number releaseGain_619 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_617);
                GrainVoiceWindow_608 = active_615 * this->minimum(attackGain_618, releaseGain_619) * level_612;
            }

            number window0_620 = GrainVoiceWindow_608;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window0_620 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot0_599))) == 0;
#endif
            number GrainReadPosition_621 = 0;

            {
                auto reverse_625 = readReverse0_604;
                auto releaseSamples_624 = voiceReleaseSamples_423;
                auto bodySamples_623 = readBody0_601;
                auto position_622 = readPos0_600;
                GrainReadPosition_621 = ((bool)(reverse_625) ? bodySamples_623 + releaseSamples_624 - 1 - position_622 : position_622);
            }

            number samplePos0_626 = GrainReadPosition_621;
            number voiceIndex0_627 = readSlot0_599 * slotSize_214 + ((readStart0_605 + samplePos0_626 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart0_605 + samplePos0_626 < 0 ? 0 : readStart0_605 + samplePos0_626)));
            number peek_62 = 0;
            number peek_63 = 0;
            auto result_628 = this->peek_default(this->gen_01_poolL_61, voiceIndex0_627, 0);
            peek_63 = result_628[1];
            peek_62 = result_628[0];
            number PanLeftGain_629 = 0;

            {
                auto pan_630 = readPan0_606;
                PanLeftGain_629 = (pan_630 > 0 ? 1 - pan_630 : 1);
            }

            number voiceL0_631 = peek_62 * window0_620 * PanLeftGain_629;
            number peek_64 = 0;
            number peek_65 = 0;
            auto result_632 = this->peek_default(this->gen_01_poolR_62, voiceIndex0_627, 0);
            peek_65 = result_632[1];
            peek_64 = result_632[0];
            number PanRightGain_633 = 0;

            {
                auto pan_634 = readPan0_606;
                PanRightGain_633 = (pan_634 < 0 ? 1 + pan_634 : 1);
            }

            number voiceR0_635 = peek_64 * window0_620 * PanRightGain_633;
            if (readPan0_606 < 0) voiceL0_631 = (voiceL0_631 + peek_64 * window0_620 * (-readPan0_606)) / (1 - readPan0_606);
            if (readPan0_606 > 0) voiceR0_635 = (voiceR0_635 + peek_62 * window0_620 * readPan0_606) / (1 + readPan0_606);
            __gen_01_voiceSlot0_98_value = ((bool)(resetNow_233) ? 0 : readSlot0_599);
            __gen_01_voicePos0_99_value = ((bool)(resetNow_233) ? 1048576 : readPos0_600 + active0_607);
            __gen_01_voiceBody0_100_value = readBody0_601;
            __gen_01_voiceAttack0_101_value = readAttack0_602;
            __gen_01_voiceLevel0_102_value = ((bool)(resetNow_233) ? 0 : readLevel0_603);
            __gen_01_voiceReverse0_103_value = ((bool)(resetNow_233) ? 0 : readReverse0_604);
            __gen_01_voicePan0_146_value = ((bool)(resetNow_233) ? 0 : readPan0_606);
            __gen_01_voiceStart0_154_value = ((bool)(resetNow_233) ? 0 : readStart0_605);
            number readSlot1_636 = ((bool)(assign1_592) ? selectedSlot : __gen_01_voiceSlot1_104_value);
            number readPos1_637 = ((bool)(assign1_592) ? 0 : __gen_01_voicePos1_105_value);
            number readBody1_638 = ((bool)(assign1_592) ? selectedBodySamples_429 : __gen_01_voiceBody1_106_value);
            number readAttack1_639 = ((bool)(assign1_592) ? selectedAttackSamples_430 : __gen_01_voiceAttack1_107_value);
            number readLevel1_640 = ((bool)(assign1_592) ? selectedLevel : __gen_01_voiceLevel1_108_value);
            number readReverse1_641 = ((bool)(assign1_592) ? reverseChoice_464 : __gen_01_voiceReverse1_109_value);
            number readStart1_642 = ((bool)(assign1_592) ? selectedVoiceStart_465 : __gen_01_voiceStart1_155_value);
            number readPan1_643 = ((bool)(assign1_592) ? selectedPan_477 : __gen_01_voicePan1_147_value);
            number active1_644 = (readPos1_637 < readBody1_638 + this->sr * 0.01) * hasPool_478 * (readLevel1_640 > 0);
            number GrainVoiceWindow_645 = 0;

            {
                auto hasPool_650 = hasPool_478;
                auto level_649 = readLevel1_640;
                auto attackSamples_648 = readAttack1_639;
                auto bodySamples_647 = readBody1_638;
                auto position_646 = readPos1_637;
                auto releaseSamples_651 = this->maximum(16, this->sr * 0.01);
                number active_652 = (position_646 < bodySamples_647 + releaseSamples_651) * hasPool_650 * (level_649 > 0);

                number attackPhase_653 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_648) == 0. ? 0. : position_646 / this->maximum(1, attackSamples_648)),
                    0,
                    1
                );

                number releasePhase_654 = (((releaseSamples_651 == 0. ? 0. : (bodySamples_647 + releaseSamples_651 - position_646) / releaseSamples_651)) > 1 ? 1 : (((releaseSamples_651 == 0. ? 0. : (bodySamples_647 + releaseSamples_651 - position_646) / releaseSamples_651)) < 0 ? 0 : (releaseSamples_651 == 0. ? 0. : (bodySamples_647 + releaseSamples_651 - position_646) / releaseSamples_651)));
                number attackGain_655 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_653);
                number releaseGain_656 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_654);
                GrainVoiceWindow_645 = active_652 * this->minimum(attackGain_655, releaseGain_656) * level_649;
            }

            number window1_657 = GrainVoiceWindow_645;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window1_657 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot1_636))) == 0;
#endif
            number GrainReadPosition_658 = 0;

            {
                auto reverse_662 = readReverse1_641;
                auto releaseSamples_661 = voiceReleaseSamples_423;
                auto bodySamples_660 = readBody1_638;
                auto position_659 = readPos1_637;
                GrainReadPosition_658 = ((bool)(reverse_662) ? bodySamples_660 + releaseSamples_661 - 1 - position_659 : position_659);
            }

            number samplePos1_663 = GrainReadPosition_658;
            number voiceIndex1_664 = readSlot1_636 * slotSize_214 + ((readStart1_642 + samplePos1_663 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart1_642 + samplePos1_663 < 0 ? 0 : readStart1_642 + samplePos1_663)));
            number peek_66 = 0;
            number peek_67 = 0;
            auto result_665 = this->peek_default(this->gen_01_poolL_61, voiceIndex1_664, 0);
            peek_67 = result_665[1];
            peek_66 = result_665[0];
            number PanLeftGain_666 = 0;

            {
                auto pan_667 = readPan1_643;
                PanLeftGain_666 = (pan_667 > 0 ? 1 - pan_667 : 1);
            }

            number voiceL1_668 = peek_66 * window1_657 * PanLeftGain_666;
            number peek_68 = 0;
            number peek_69 = 0;
            auto result_669 = this->peek_default(this->gen_01_poolR_62, voiceIndex1_664, 0);
            peek_69 = result_669[1];
            peek_68 = result_669[0];
            number PanRightGain_670 = 0;

            {
                auto pan_671 = readPan1_643;
                PanRightGain_670 = (pan_671 < 0 ? 1 + pan_671 : 1);
            }

            number voiceR1_672 = peek_68 * window1_657 * PanRightGain_670;
            if (readPan1_643 < 0) voiceL1_668 = (voiceL1_668 + peek_68 * window1_657 * (-readPan1_643)) / (1 - readPan1_643);
            if (readPan1_643 > 0) voiceR1_672 = (voiceR1_672 + peek_66 * window1_657 * readPan1_643) / (1 + readPan1_643);
            __gen_01_voiceSlot1_104_value = ((bool)(resetNow_233) ? 0 : readSlot1_636);
            __gen_01_voicePos1_105_value = ((bool)(resetNow_233) ? 1048576 : readPos1_637 + active1_644);
            __gen_01_voiceBody1_106_value = readBody1_638;
            __gen_01_voiceAttack1_107_value = readAttack1_639;
            __gen_01_voiceLevel1_108_value = ((bool)(resetNow_233) ? 0 : readLevel1_640);
            __gen_01_voiceReverse1_109_value = ((bool)(resetNow_233) ? 0 : readReverse1_641);
            __gen_01_voicePan1_147_value = ((bool)(resetNow_233) ? 0 : readPan1_643);
            __gen_01_voiceStart1_155_value = ((bool)(resetNow_233) ? 0 : readStart1_642);
            number readSlot2_673 = ((bool)(assign2_593) ? selectedSlot : __gen_01_voiceSlot2_110_value);
            number readPos2_674 = ((bool)(assign2_593) ? 0 : __gen_01_voicePos2_111_value);
            number readBody2_675 = ((bool)(assign2_593) ? selectedBodySamples_429 : __gen_01_voiceBody2_112_value);
            number readAttack2_676 = ((bool)(assign2_593) ? selectedAttackSamples_430 : __gen_01_voiceAttack2_113_value);
            number readLevel2_677 = ((bool)(assign2_593) ? selectedLevel : __gen_01_voiceLevel2_114_value);
            number readReverse2_678 = ((bool)(assign2_593) ? reverseChoice_464 : __gen_01_voiceReverse2_115_value);
            number readStart2_679 = ((bool)(assign2_593) ? selectedVoiceStart_465 : __gen_01_voiceStart2_156_value);
            number readPan2_680 = ((bool)(assign2_593) ? selectedPan_477 : __gen_01_voicePan2_148_value);
            number active2_681 = (readPos2_674 < readBody2_675 + this->sr * 0.01) * hasPool_478 * (readLevel2_677 > 0);
            number GrainVoiceWindow_682 = 0;

            {
                auto hasPool_687 = hasPool_478;
                auto level_686 = readLevel2_677;
                auto attackSamples_685 = readAttack2_676;
                auto bodySamples_684 = readBody2_675;
                auto position_683 = readPos2_674;
                auto releaseSamples_688 = this->maximum(16, this->sr * 0.01);
                number active_689 = (position_683 < bodySamples_684 + releaseSamples_688) * hasPool_687 * (level_686 > 0);

                number attackPhase_690 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_685) == 0. ? 0. : position_683 / this->maximum(1, attackSamples_685)),
                    0,
                    1
                );

                number releasePhase_691 = (((releaseSamples_688 == 0. ? 0. : (bodySamples_684 + releaseSamples_688 - position_683) / releaseSamples_688)) > 1 ? 1 : (((releaseSamples_688 == 0. ? 0. : (bodySamples_684 + releaseSamples_688 - position_683) / releaseSamples_688)) < 0 ? 0 : (releaseSamples_688 == 0. ? 0. : (bodySamples_684 + releaseSamples_688 - position_683) / releaseSamples_688)));
                number attackGain_692 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_690);
                number releaseGain_693 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_691);
                GrainVoiceWindow_682 = active_689 * this->minimum(attackGain_692, releaseGain_693) * level_686;
            }

            number window2_694 = GrainVoiceWindow_682;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window2_694 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot2_673))) == 0;
#endif
            number GrainReadPosition_695 = 0;

            {
                auto reverse_699 = readReverse2_678;
                auto releaseSamples_698 = voiceReleaseSamples_423;
                auto bodySamples_697 = readBody2_675;
                auto position_696 = readPos2_674;
                GrainReadPosition_695 = ((bool)(reverse_699) ? bodySamples_697 + releaseSamples_698 - 1 - position_696 : position_696);
            }

            number samplePos2_700 = GrainReadPosition_695;
            number voiceIndex2_701 = readSlot2_673 * slotSize_214 + ((readStart2_679 + samplePos2_700 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart2_679 + samplePos2_700 < 0 ? 0 : readStart2_679 + samplePos2_700)));
            number peek_70 = 0;
            number peek_71 = 0;
            auto result_702 = this->peek_default(this->gen_01_poolL_61, voiceIndex2_701, 0);
            peek_71 = result_702[1];
            peek_70 = result_702[0];
            number PanLeftGain_703 = 0;

            {
                auto pan_704 = readPan2_680;
                PanLeftGain_703 = (pan_704 > 0 ? 1 - pan_704 : 1);
            }

            number voiceL2_705 = peek_70 * window2_694 * PanLeftGain_703;
            number peek_72 = 0;
            number peek_73 = 0;
            auto result_706 = this->peek_default(this->gen_01_poolR_62, voiceIndex2_701, 0);
            peek_73 = result_706[1];
            peek_72 = result_706[0];
            number PanRightGain_707 = 0;

            {
                auto pan_708 = readPan2_680;
                PanRightGain_707 = (pan_708 < 0 ? 1 + pan_708 : 1);
            }

            number voiceR2_709 = peek_72 * window2_694 * PanRightGain_707;
            if (readPan2_680 < 0) voiceL2_705 = (voiceL2_705 + peek_72 * window2_694 * (-readPan2_680)) / (1 - readPan2_680);
            if (readPan2_680 > 0) voiceR2_709 = (voiceR2_709 + peek_70 * window2_694 * readPan2_680) / (1 + readPan2_680);
            __gen_01_voiceSlot2_110_value = ((bool)(resetNow_233) ? 0 : readSlot2_673);
            __gen_01_voicePos2_111_value = ((bool)(resetNow_233) ? 1048576 : readPos2_674 + active2_681);
            __gen_01_voiceBody2_112_value = readBody2_675;
            __gen_01_voiceAttack2_113_value = readAttack2_676;
            __gen_01_voiceLevel2_114_value = ((bool)(resetNow_233) ? 0 : readLevel2_677);
            __gen_01_voiceReverse2_115_value = ((bool)(resetNow_233) ? 0 : readReverse2_678);
            __gen_01_voicePan2_148_value = ((bool)(resetNow_233) ? 0 : readPan2_680);
            __gen_01_voiceStart2_156_value = ((bool)(resetNow_233) ? 0 : readStart2_679);
            number readSlot3_710 = ((bool)(assign3_594) ? selectedSlot : __gen_01_voiceSlot3_116_value);
            number readPos3_711 = ((bool)(assign3_594) ? 0 : __gen_01_voicePos3_117_value);
            number readBody3_712 = ((bool)(assign3_594) ? selectedBodySamples_429 : __gen_01_voiceBody3_118_value);
            number readAttack3_713 = ((bool)(assign3_594) ? selectedAttackSamples_430 : __gen_01_voiceAttack3_119_value);
            number readLevel3_714 = ((bool)(assign3_594) ? selectedLevel : __gen_01_voiceLevel3_120_value);
            number readReverse3_715 = ((bool)(assign3_594) ? reverseChoice_464 : __gen_01_voiceReverse3_121_value);
            number readStart3_716 = ((bool)(assign3_594) ? selectedVoiceStart_465 : __gen_01_voiceStart3_157_value);
            number readPan3_717 = ((bool)(assign3_594) ? selectedPan_477 : __gen_01_voicePan3_149_value);
            number active3_718 = (readPos3_711 < readBody3_712 + this->sr * 0.01) * hasPool_478 * (readLevel3_714 > 0);
            number GrainVoiceWindow_719 = 0;

            {
                auto hasPool_724 = hasPool_478;
                auto level_723 = readLevel3_714;
                auto attackSamples_722 = readAttack3_713;
                auto bodySamples_721 = readBody3_712;
                auto position_720 = readPos3_711;
                auto releaseSamples_725 = this->maximum(16, this->sr * 0.01);
                number active_726 = (position_720 < bodySamples_721 + releaseSamples_725) * hasPool_724 * (level_723 > 0);

                number attackPhase_727 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_722) == 0. ? 0. : position_720 / this->maximum(1, attackSamples_722)),
                    0,
                    1
                );

                number releasePhase_728 = (((releaseSamples_725 == 0. ? 0. : (bodySamples_721 + releaseSamples_725 - position_720) / releaseSamples_725)) > 1 ? 1 : (((releaseSamples_725 == 0. ? 0. : (bodySamples_721 + releaseSamples_725 - position_720) / releaseSamples_725)) < 0 ? 0 : (releaseSamples_725 == 0. ? 0. : (bodySamples_721 + releaseSamples_725 - position_720) / releaseSamples_725)));
                number attackGain_729 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_727);
                number releaseGain_730 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_728);
                GrainVoiceWindow_719 = active_726 * this->minimum(attackGain_729, releaseGain_730) * level_723;
            }

            number window3_731 = GrainVoiceWindow_719;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window3_731 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot3_710))) == 0;
#endif
            number GrainReadPosition_732 = 0;

            {
                auto reverse_736 = readReverse3_715;
                auto releaseSamples_735 = voiceReleaseSamples_423;
                auto bodySamples_734 = readBody3_712;
                auto position_733 = readPos3_711;
                GrainReadPosition_732 = ((bool)(reverse_736) ? bodySamples_734 + releaseSamples_735 - 1 - position_733 : position_733);
            }

            number samplePos3_737 = GrainReadPosition_732;
            number voiceIndex3_738 = readSlot3_710 * slotSize_214 + ((readStart3_716 + samplePos3_737 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart3_716 + samplePos3_737 < 0 ? 0 : readStart3_716 + samplePos3_737)));
            number peek_74 = 0;
            number peek_75 = 0;
            auto result_739 = this->peek_default(this->gen_01_poolL_61, voiceIndex3_738, 0);
            peek_75 = result_739[1];
            peek_74 = result_739[0];
            number PanLeftGain_740 = 0;

            {
                auto pan_741 = readPan3_717;
                PanLeftGain_740 = (pan_741 > 0 ? 1 - pan_741 : 1);
            }

            number voiceL3_742 = peek_74 * window3_731 * PanLeftGain_740;
            number peek_76 = 0;
            number peek_77 = 0;
            auto result_743 = this->peek_default(this->gen_01_poolR_62, voiceIndex3_738, 0);
            peek_77 = result_743[1];
            peek_76 = result_743[0];
            number PanRightGain_744 = 0;

            {
                auto pan_745 = readPan3_717;
                PanRightGain_744 = (pan_745 < 0 ? 1 + pan_745 : 1);
            }

            number voiceR3_746 = peek_76 * window3_731 * PanRightGain_744;
            if (readPan3_717 < 0) voiceL3_742 = (voiceL3_742 + peek_76 * window3_731 * (-readPan3_717)) / (1 - readPan3_717);
            if (readPan3_717 > 0) voiceR3_746 = (voiceR3_746 + peek_74 * window3_731 * readPan3_717) / (1 + readPan3_717);
            __gen_01_voiceSlot3_116_value = ((bool)(resetNow_233) ? 0 : readSlot3_710);
            __gen_01_voicePos3_117_value = ((bool)(resetNow_233) ? 1048576 : readPos3_711 + active3_718);
            __gen_01_voiceBody3_118_value = readBody3_712;
            __gen_01_voiceAttack3_119_value = readAttack3_713;
            __gen_01_voiceLevel3_120_value = ((bool)(resetNow_233) ? 0 : readLevel3_714);
            __gen_01_voiceReverse3_121_value = ((bool)(resetNow_233) ? 0 : readReverse3_715);
            __gen_01_voicePan3_149_value = ((bool)(resetNow_233) ? 0 : readPan3_717);
            __gen_01_voiceStart3_157_value = ((bool)(resetNow_233) ? 0 : readStart3_716);
            number readSlot4_747 = ((bool)(assign4_595) ? selectedSlot : __gen_01_voiceSlot4_122_value);
            number readPos4_748 = ((bool)(assign4_595) ? 0 : __gen_01_voicePos4_123_value);
            number readBody4_749 = ((bool)(assign4_595) ? selectedBodySamples_429 : __gen_01_voiceBody4_124_value);
            number readAttack4_750 = ((bool)(assign4_595) ? selectedAttackSamples_430 : __gen_01_voiceAttack4_125_value);
            number readLevel4_751 = ((bool)(assign4_595) ? selectedLevel : __gen_01_voiceLevel4_126_value);
            number readReverse4_752 = ((bool)(assign4_595) ? reverseChoice_464 : __gen_01_voiceReverse4_127_value);
            number readStart4_753 = ((bool)(assign4_595) ? selectedVoiceStart_465 : __gen_01_voiceStart4_158_value);
            number readPan4_754 = ((bool)(assign4_595) ? selectedPan_477 : __gen_01_voicePan4_150_value);
            number active4_755 = (readPos4_748 < readBody4_749 + this->sr * 0.01) * hasPool_478 * (readLevel4_751 > 0);
            number GrainVoiceWindow_756 = 0;

            {
                auto hasPool_761 = hasPool_478;
                auto level_760 = readLevel4_751;
                auto attackSamples_759 = readAttack4_750;
                auto bodySamples_758 = readBody4_749;
                auto position_757 = readPos4_748;
                auto releaseSamples_762 = this->maximum(16, this->sr * 0.01);
                number active_763 = (position_757 < bodySamples_758 + releaseSamples_762) * hasPool_761 * (level_760 > 0);

                number attackPhase_764 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_759) == 0. ? 0. : position_757 / this->maximum(1, attackSamples_759)),
                    0,
                    1
                );

                number releasePhase_765 = (((releaseSamples_762 == 0. ? 0. : (bodySamples_758 + releaseSamples_762 - position_757) / releaseSamples_762)) > 1 ? 1 : (((releaseSamples_762 == 0. ? 0. : (bodySamples_758 + releaseSamples_762 - position_757) / releaseSamples_762)) < 0 ? 0 : (releaseSamples_762 == 0. ? 0. : (bodySamples_758 + releaseSamples_762 - position_757) / releaseSamples_762)));
                number attackGain_766 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_764);
                number releaseGain_767 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_765);
                GrainVoiceWindow_756 = active_763 * this->minimum(attackGain_766, releaseGain_767) * level_760;
            }

            number window4_768 = GrainVoiceWindow_756;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window4_768 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot4_747))) == 0;
#endif
            number GrainReadPosition_769 = 0;

            {
                auto reverse_773 = readReverse4_752;
                auto releaseSamples_772 = voiceReleaseSamples_423;
                auto bodySamples_771 = readBody4_749;
                auto position_770 = readPos4_748;
                GrainReadPosition_769 = ((bool)(reverse_773) ? bodySamples_771 + releaseSamples_772 - 1 - position_770 : position_770);
            }

            number samplePos4_774 = GrainReadPosition_769;
            number voiceIndex4_775 = readSlot4_747 * slotSize_214 + ((readStart4_753 + samplePos4_774 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart4_753 + samplePos4_774 < 0 ? 0 : readStart4_753 + samplePos4_774)));
            number peek_78 = 0;
            number peek_79 = 0;
            auto result_776 = this->peek_default(this->gen_01_poolL_61, voiceIndex4_775, 0);
            peek_79 = result_776[1];
            peek_78 = result_776[0];
            number PanLeftGain_777 = 0;

            {
                auto pan_778 = readPan4_754;
                PanLeftGain_777 = (pan_778 > 0 ? 1 - pan_778 : 1);
            }

            number voiceL4_779 = peek_78 * window4_768 * PanLeftGain_777;
            number peek_80 = 0;
            number peek_81 = 0;
            auto result_780 = this->peek_default(this->gen_01_poolR_62, voiceIndex4_775, 0);
            peek_81 = result_780[1];
            peek_80 = result_780[0];
            number PanRightGain_781 = 0;

            {
                auto pan_782 = readPan4_754;
                PanRightGain_781 = (pan_782 < 0 ? 1 + pan_782 : 1);
            }

            number voiceR4_783 = peek_80 * window4_768 * PanRightGain_781;
            if (readPan4_754 < 0) voiceL4_779 = (voiceL4_779 + peek_80 * window4_768 * (-readPan4_754)) / (1 - readPan4_754);
            if (readPan4_754 > 0) voiceR4_783 = (voiceR4_783 + peek_78 * window4_768 * readPan4_754) / (1 + readPan4_754);
            __gen_01_voiceSlot4_122_value = ((bool)(resetNow_233) ? 0 : readSlot4_747);
            __gen_01_voicePos4_123_value = ((bool)(resetNow_233) ? 1048576 : readPos4_748 + active4_755);
            __gen_01_voiceBody4_124_value = readBody4_749;
            __gen_01_voiceAttack4_125_value = readAttack4_750;
            __gen_01_voiceLevel4_126_value = ((bool)(resetNow_233) ? 0 : readLevel4_751);
            __gen_01_voiceReverse4_127_value = ((bool)(resetNow_233) ? 0 : readReverse4_752);
            __gen_01_voicePan4_150_value = ((bool)(resetNow_233) ? 0 : readPan4_754);
            __gen_01_voiceStart4_158_value = ((bool)(resetNow_233) ? 0 : readStart4_753);
            number readSlot5_784 = ((bool)(assign5_596) ? selectedSlot : __gen_01_voiceSlot5_128_value);
            number readPos5_785 = ((bool)(assign5_596) ? 0 : __gen_01_voicePos5_129_value);
            number readBody5_786 = ((bool)(assign5_596) ? selectedBodySamples_429 : __gen_01_voiceBody5_130_value);
            number readAttack5_787 = ((bool)(assign5_596) ? selectedAttackSamples_430 : __gen_01_voiceAttack5_131_value);
            number readLevel5_788 = ((bool)(assign5_596) ? selectedLevel : __gen_01_voiceLevel5_132_value);
            number readReverse5_789 = ((bool)(assign5_596) ? reverseChoice_464 : __gen_01_voiceReverse5_133_value);
            number readStart5_790 = ((bool)(assign5_596) ? selectedVoiceStart_465 : __gen_01_voiceStart5_159_value);
            number readPan5_791 = ((bool)(assign5_596) ? selectedPan_477 : __gen_01_voicePan5_151_value);
            number active5_792 = (readPos5_785 < readBody5_786 + this->sr * 0.01) * hasPool_478 * (readLevel5_788 > 0);
            number GrainVoiceWindow_793 = 0;

            {
                auto hasPool_798 = hasPool_478;
                auto level_797 = readLevel5_788;
                auto attackSamples_796 = readAttack5_787;
                auto bodySamples_795 = readBody5_786;
                auto position_794 = readPos5_785;
                auto releaseSamples_799 = this->maximum(16, this->sr * 0.01);
                number active_800 = (position_794 < bodySamples_795 + releaseSamples_799) * hasPool_798 * (level_797 > 0);

                number attackPhase_801 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_796) == 0. ? 0. : position_794 / this->maximum(1, attackSamples_796)),
                    0,
                    1
                );

                number releasePhase_802 = (((releaseSamples_799 == 0. ? 0. : (bodySamples_795 + releaseSamples_799 - position_794) / releaseSamples_799)) > 1 ? 1 : (((releaseSamples_799 == 0. ? 0. : (bodySamples_795 + releaseSamples_799 - position_794) / releaseSamples_799)) < 0 ? 0 : (releaseSamples_799 == 0. ? 0. : (bodySamples_795 + releaseSamples_799 - position_794) / releaseSamples_799)));
                number attackGain_803 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_801);
                number releaseGain_804 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_802);
                GrainVoiceWindow_793 = active_800 * this->minimum(attackGain_803, releaseGain_804) * level_797;
            }

            number window5_805 = GrainVoiceWindow_793;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window5_805 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot5_784))) == 0;
#endif
            number GrainReadPosition_806 = 0;

            {
                auto reverse_810 = readReverse5_789;
                auto releaseSamples_809 = voiceReleaseSamples_423;
                auto bodySamples_808 = readBody5_786;
                auto position_807 = readPos5_785;
                GrainReadPosition_806 = ((bool)(reverse_810) ? bodySamples_808 + releaseSamples_809 - 1 - position_807 : position_807);
            }

            number samplePos5_811 = GrainReadPosition_806;
            number voiceIndex5_812 = readSlot5_784 * slotSize_214 + ((readStart5_790 + samplePos5_811 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart5_790 + samplePos5_811 < 0 ? 0 : readStart5_790 + samplePos5_811)));
            number peek_82 = 0;
            number peek_83 = 0;
            auto result_813 = this->peek_default(this->gen_01_poolL_61, voiceIndex5_812, 0);
            peek_83 = result_813[1];
            peek_82 = result_813[0];
            number PanLeftGain_814 = 0;

            {
                auto pan_815 = readPan5_791;
                PanLeftGain_814 = (pan_815 > 0 ? 1 - pan_815 : 1);
            }

            number voiceL5_816 = peek_82 * window5_805 * PanLeftGain_814;
            number peek_84 = 0;
            number peek_85 = 0;
            auto result_817 = this->peek_default(this->gen_01_poolR_62, voiceIndex5_812, 0);
            peek_85 = result_817[1];
            peek_84 = result_817[0];
            number PanRightGain_818 = 0;

            {
                auto pan_819 = readPan5_791;
                PanRightGain_818 = (pan_819 < 0 ? 1 + pan_819 : 1);
            }

            number voiceR5_820 = peek_84 * window5_805 * PanRightGain_818;
            if (readPan5_791 < 0) voiceL5_816 = (voiceL5_816 + peek_84 * window5_805 * (-readPan5_791)) / (1 - readPan5_791);
            if (readPan5_791 > 0) voiceR5_820 = (voiceR5_820 + peek_82 * window5_805 * readPan5_791) / (1 + readPan5_791);
            __gen_01_voiceSlot5_128_value = ((bool)(resetNow_233) ? 0 : readSlot5_784);
            __gen_01_voicePos5_129_value = ((bool)(resetNow_233) ? 1048576 : readPos5_785 + active5_792);
            __gen_01_voiceBody5_130_value = readBody5_786;
            __gen_01_voiceAttack5_131_value = readAttack5_787;
            __gen_01_voiceLevel5_132_value = ((bool)(resetNow_233) ? 0 : readLevel5_788);
            __gen_01_voiceReverse5_133_value = ((bool)(resetNow_233) ? 0 : readReverse5_789);
            __gen_01_voicePan5_151_value = ((bool)(resetNow_233) ? 0 : readPan5_791);
            __gen_01_voiceStart5_159_value = ((bool)(resetNow_233) ? 0 : readStart5_790);
            number readSlot6_821 = ((bool)(assign6_597) ? selectedSlot : __gen_01_voiceSlot6_134_value);
            number readPos6_822 = ((bool)(assign6_597) ? 0 : __gen_01_voicePos6_135_value);
            number readBody6_823 = ((bool)(assign6_597) ? selectedBodySamples_429 : __gen_01_voiceBody6_136_value);
            number readAttack6_824 = ((bool)(assign6_597) ? selectedAttackSamples_430 : __gen_01_voiceAttack6_137_value);
            number readLevel6_825 = ((bool)(assign6_597) ? selectedLevel : __gen_01_voiceLevel6_138_value);
            number readReverse6_826 = ((bool)(assign6_597) ? reverseChoice_464 : __gen_01_voiceReverse6_139_value);
            number readStart6_827 = ((bool)(assign6_597) ? selectedVoiceStart_465 : __gen_01_voiceStart6_160_value);
            number readPan6_828 = ((bool)(assign6_597) ? selectedPan_477 : __gen_01_voicePan6_152_value);
            number active6_829 = (readPos6_822 < readBody6_823 + this->sr * 0.01) * hasPool_478 * (readLevel6_825 > 0);
            number GrainVoiceWindow_830 = 0;

            {
                auto hasPool_835 = hasPool_478;
                auto level_834 = readLevel6_825;
                auto attackSamples_833 = readAttack6_824;
                auto bodySamples_832 = readBody6_823;
                auto position_831 = readPos6_822;
                auto releaseSamples_836 = this->maximum(16, this->sr * 0.01);
                number active_837 = (position_831 < bodySamples_832 + releaseSamples_836) * hasPool_835 * (level_834 > 0);

                number attackPhase_838 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_833) == 0. ? 0. : position_831 / this->maximum(1, attackSamples_833)),
                    0,
                    1
                );

                number releasePhase_839 = (((releaseSamples_836 == 0. ? 0. : (bodySamples_832 + releaseSamples_836 - position_831) / releaseSamples_836)) > 1 ? 1 : (((releaseSamples_836 == 0. ? 0. : (bodySamples_832 + releaseSamples_836 - position_831) / releaseSamples_836)) < 0 ? 0 : (releaseSamples_836 == 0. ? 0. : (bodySamples_832 + releaseSamples_836 - position_831) / releaseSamples_836)));
                number attackGain_840 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_838);
                number releaseGain_841 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_839);
                GrainVoiceWindow_830 = active_837 * this->minimum(attackGain_840, releaseGain_841) * level_834;
            }

            number window6_842 = GrainVoiceWindow_830;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window6_842 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot6_821))) == 0;
#endif
            number GrainReadPosition_843 = 0;

            {
                auto reverse_847 = readReverse6_826;
                auto releaseSamples_846 = voiceReleaseSamples_423;
                auto bodySamples_845 = readBody6_823;
                auto position_844 = readPos6_822;
                GrainReadPosition_843 = ((bool)(reverse_847) ? bodySamples_845 + releaseSamples_846 - 1 - position_844 : position_844);
            }

            number samplePos6_848 = GrainReadPosition_843;
            number voiceIndex6_849 = readSlot6_821 * slotSize_214 + ((readStart6_827 + samplePos6_848 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart6_827 + samplePos6_848 < 0 ? 0 : readStart6_827 + samplePos6_848)));
            number peek_86 = 0;
            number peek_87 = 0;
            auto result_850 = this->peek_default(this->gen_01_poolL_61, voiceIndex6_849, 0);
            peek_87 = result_850[1];
            peek_86 = result_850[0];
            number PanLeftGain_851 = 0;

            {
                auto pan_852 = readPan6_828;
                PanLeftGain_851 = (pan_852 > 0 ? 1 - pan_852 : 1);
            }

            number voiceL6_853 = peek_86 * window6_842 * PanLeftGain_851;
            number peek_88 = 0;
            number peek_89 = 0;
            auto result_854 = this->peek_default(this->gen_01_poolR_62, voiceIndex6_849, 0);
            peek_89 = result_854[1];
            peek_88 = result_854[0];
            number PanRightGain_855 = 0;

            {
                auto pan_856 = readPan6_828;
                PanRightGain_855 = (pan_856 < 0 ? 1 + pan_856 : 1);
            }

            number voiceR6_857 = peek_88 * window6_842 * PanRightGain_855;
            if (readPan6_828 < 0) voiceL6_853 = (voiceL6_853 + peek_88 * window6_842 * (-readPan6_828)) / (1 - readPan6_828);
            if (readPan6_828 > 0) voiceR6_857 = (voiceR6_857 + peek_86 * window6_842 * readPan6_828) / (1 + readPan6_828);
            __gen_01_voiceSlot6_134_value = ((bool)(resetNow_233) ? 0 : readSlot6_821);
            __gen_01_voicePos6_135_value = ((bool)(resetNow_233) ? 1048576 : readPos6_822 + active6_829);
            __gen_01_voiceBody6_136_value = readBody6_823;
            __gen_01_voiceAttack6_137_value = readAttack6_824;
            __gen_01_voiceLevel6_138_value = ((bool)(resetNow_233) ? 0 : readLevel6_825);
            __gen_01_voiceReverse6_139_value = ((bool)(resetNow_233) ? 0 : readReverse6_826);
            __gen_01_voicePan6_152_value = ((bool)(resetNow_233) ? 0 : readPan6_828);
            __gen_01_voiceStart6_160_value = ((bool)(resetNow_233) ? 0 : readStart6_827);
            number readSlot7_858 = ((bool)(assign7_598) ? selectedSlot : __gen_01_voiceSlot7_140_value);
            number readPos7_859 = ((bool)(assign7_598) ? 0 : __gen_01_voicePos7_141_value);
            number readBody7_860 = ((bool)(assign7_598) ? selectedBodySamples_429 : __gen_01_voiceBody7_142_value);
            number readAttack7_861 = ((bool)(assign7_598) ? selectedAttackSamples_430 : __gen_01_voiceAttack7_143_value);
            number readLevel7_862 = ((bool)(assign7_598) ? selectedLevel : __gen_01_voiceLevel7_144_value);
            number readReverse7_863 = ((bool)(assign7_598) ? reverseChoice_464 : __gen_01_voiceReverse7_145_value);
            number readStart7_864 = ((bool)(assign7_598) ? selectedVoiceStart_465 : __gen_01_voiceStart7_161_value);
            number readPan7_865 = ((bool)(assign7_598) ? selectedPan_477 : __gen_01_voicePan7_153_value);
            number active7_866 = (readPos7_859 < readBody7_860 + this->sr * 0.01) * hasPool_478 * (readLevel7_862 > 0);
            number GrainVoiceWindow_867 = 0;

            {
                auto hasPool_872 = hasPool_478;
                auto level_871 = readLevel7_862;
                auto attackSamples_870 = readAttack7_861;
                auto bodySamples_869 = readBody7_860;
                auto position_868 = readPos7_859;
                auto releaseSamples_873 = this->maximum(16, this->sr * 0.01);
                number active_874 = (position_868 < bodySamples_869 + releaseSamples_873) * hasPool_872 * (level_871 > 0);

                number attackPhase_875 = this->__wrapped_op_clamp(
                    (this->maximum(1, attackSamples_870) == 0. ? 0. : position_868 / this->maximum(1, attackSamples_870)),
                    0,
                    1
                );

                number releasePhase_876 = (((releaseSamples_873 == 0. ? 0. : (bodySamples_869 + releaseSamples_873 - position_868) / releaseSamples_873)) > 1 ? 1 : (((releaseSamples_873 == 0. ? 0. : (bodySamples_869 + releaseSamples_873 - position_868) / releaseSamples_873)) < 0 ? 0 : (releaseSamples_873 == 0. ? 0. : (bodySamples_869 + releaseSamples_873 - position_868) / releaseSamples_873)));
                number attackGain_877 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * attackPhase_875);
                number releaseGain_878 = 0.5 - 0.5 * rnbo_cos(3.14159265358979323846 * releasePhase_876);
                GrainVoiceWindow_867 = active_874 * this->minimum(attackGain_877, releaseGain_878) * level_871;
            }

            number window7_879 = GrainVoiceWindow_867;
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            window7_879 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(readSlot7_858))) == 0;
#endif
            number GrainReadPosition_880 = 0;

            {
                auto reverse_884 = readReverse7_863;
                auto releaseSamples_883 = voiceReleaseSamples_423;
                auto bodySamples_882 = readBody7_860;
                auto position_881 = readPos7_859;
                GrainReadPosition_880 = ((bool)(reverse_884) ? bodySamples_882 + releaseSamples_883 - 1 - position_881 : position_881);
            }

            number samplePos7_885 = GrainReadPosition_880;
            number voiceIndex7_886 = readSlot7_858 * slotSize_214 + ((readStart7_864 + samplePos7_885 > slotSize_214 - 2 ? slotSize_214 - 2 : (readStart7_864 + samplePos7_885 < 0 ? 0 : readStart7_864 + samplePos7_885)));
            number peek_90 = 0;
            number peek_91 = 0;
            auto result_887 = this->peek_default(this->gen_01_poolL_61, voiceIndex7_886, 0);
            peek_91 = result_887[1];
            peek_90 = result_887[0];
            number PanLeftGain_888 = 0;

            {
                auto pan_889 = readPan7_865;
                PanLeftGain_888 = (pan_889 > 0 ? 1 - pan_889 : 1);
            }

            number voiceL7_890 = peek_90 * window7_879 * PanLeftGain_888;
            number peek_92 = 0;
            number peek_93 = 0;
            auto result_891 = this->peek_default(this->gen_01_poolR_62, voiceIndex7_886, 0);
            peek_93 = result_891[1];
            peek_92 = result_891[0];
            number PanRightGain_892 = 0;

            {
                auto pan_893 = readPan7_865;
                PanRightGain_892 = (pan_893 < 0 ? 1 + pan_893 : 1);
            }

            number voiceR7_894 = peek_92 * window7_879 * PanRightGain_892;
            if (readPan7_865 < 0) voiceL7_890 = (voiceL7_890 + peek_92 * window7_879 * (-readPan7_865)) / (1 - readPan7_865);
            if (readPan7_865 > 0) voiceR7_894 = (voiceR7_894 + peek_90 * window7_879 * readPan7_865) / (1 + readPan7_865);
            __gen_01_voiceSlot7_140_value = ((bool)(resetNow_233) ? 0 : readSlot7_858);
            __gen_01_voicePos7_141_value = ((bool)(resetNow_233) ? 1048576 : readPos7_859 + active7_866);
            __gen_01_voiceBody7_142_value = readBody7_860;
            __gen_01_voiceAttack7_143_value = readAttack7_861;
            __gen_01_voiceLevel7_144_value = ((bool)(resetNow_233) ? 0 : readLevel7_862);
            __gen_01_voiceReverse7_145_value = ((bool)(resetNow_233) ? 0 : readReverse7_863);
            __gen_01_voicePan7_153_value = ((bool)(resetNow_233) ? 0 : readPan7_865);
            __gen_01_voiceStart7_161_value = ((bool)(resetNow_233) ? 0 : readStart7_864);
            __gen_01_nextVoice_97_value = ((bool)(resetNow_233) ? 0 : ((bool)(playHit_409) ? this->safemod(__gen_01_nextVoice_97_value + 1, 8) : __gen_01_nextVoice_97_value));
            number stealReadSlot_895 = ((bool)(playHit_409) ? stolenSlot_583 : __gen_01_stealSlot_163_value);
            number stealReadPosition_896 = ((bool)(playHit_409) ? stolenSamplePosition_590 : __gen_01_stealPosition_164_value);
            number stealReadDirection_897 = ((bool)(playHit_409) ? ((bool)(stolenReverse_587) ? -1 : 1) : __gen_01_stealDirection_165_value);
            number stealReadPan_898 = ((bool)(playHit_409) ? stolenPan_588 : __gen_01_stealPan_168_value);
            number stealStartGain_899 = ((bool)(playHit_409) ? stolenGain_585 : __gen_01_stealInitialGain_166_value);
            number stealFadePos_900 = ((bool)(playHit_409) ? 0 : __gen_01_stealFadePosition_167_value);
            auto stealFadeSamples_901 = this->maximum(16, this->sr * 0.003);
            number stealActive_902 = (stealFadePos_900 < stealFadeSamples_901) * (stealStartGain_899 > 0);
            number stealPhase_903 = (((stealFadeSamples_901 == 0. ? 0. : stealFadePos_900 / stealFadeSamples_901)) > 1 ? 1 : (((stealFadeSamples_901 == 0. ? 0. : stealFadePos_900 / stealFadeSamples_901)) < 0 ? 0 : (stealFadeSamples_901 == 0. ? 0. : stealFadePos_900 / stealFadeSamples_901)));
            number stealGain_904 = stealActive_902 * stealStartGain_899 * (0.5 + 0.5 * rnbo_cos(3.14159265358979323846 * stealPhase_903));
#ifdef SCATTERLOOM_MPC_CAPTURE_GUARD
            stealGain_904 *= (mpcRecordingSlots & (1u << static_cast<unsigned>(stealReadSlot_895))) == 0;
#endif
            number stealIndex_905 = stealReadSlot_895 * slotSize_214 + ((stealReadPosition_896 > slotSize_214 - 2 ? slotSize_214 - 2 : (stealReadPosition_896 < 0 ? 0 : stealReadPosition_896)));
            number peek_94 = 0;
            number peek_95 = 0;
            auto result_906 = this->peek_default(this->gen_01_poolL_61, stealIndex_905, 0);
            peek_95 = result_906[1];
            peek_94 = result_906[0];
            number PanLeftGain_907 = 0;

            {
                auto pan_908 = stealReadPan_898;
                PanLeftGain_907 = (pan_908 > 0 ? 1 - pan_908 : 1);
            }

            number stealL_909 = peek_94 * stealGain_904 * PanLeftGain_907;
            number peek_96 = 0;
            number peek_97 = 0;
            auto result_910 = this->peek_default(this->gen_01_poolR_62, stealIndex_905, 0);
            peek_97 = result_910[1];
            peek_96 = result_910[0];
            number PanRightGain_911 = 0;

            {
                auto pan_912 = stealReadPan_898;
                PanRightGain_911 = (pan_912 < 0 ? 1 + pan_912 : 1);
            }

            number stealR_913 = peek_96 * stealGain_904 * PanRightGain_911;
            if (stealReadPan_898 < 0) stealL_909 = (stealL_909 + peek_96 * stealGain_904 * (-stealReadPan_898)) / (1 - stealReadPan_898);
            if (stealReadPan_898 > 0) stealR_913 = (stealR_913 + peek_94 * stealGain_904 * stealReadPan_898) / (1 + stealReadPan_898);
            __gen_01_stealSlot_163_value = ((bool)(resetNow_233) ? 0 : stealReadSlot_895);
            __gen_01_stealPosition_164_value = ((bool)(resetNow_233) ? 1048576 : stealReadPosition_896 + stealActive_902 * stealReadDirection_897);
            __gen_01_stealDirection_165_value = ((bool)(resetNow_233) ? 1 : stealReadDirection_897);
            __gen_01_stealInitialGain_166_value = ((bool)(resetNow_233) ? 0 : stealStartGain_899);
            __gen_01_stealFadePosition_167_value = ((bool)(resetNow_233) ? 1048576 : stealFadePos_900 + stealActive_902);
            __gen_01_stealPan_168_value = ((bool)(resetNow_233) ? 0 : stealReadPan_898);
            number patternGrainL_914 = voiceL0_631 + voiceL1_668 + voiceL2_705 + voiceL3_742 + voiceL4_779 + voiceL5_816 + voiceL6_853 + voiceL7_890 + stealL_909;
            number patternGrainR_915 = voiceR0_635 + voiceR1_672 + voiceR2_709 + voiceR3_746 + voiceR4_783 + voiceR5_820 + voiceR6_857 + voiceR7_894 + stealR_913;
            auto loopDelayTolerance_916 = this->maximum(16, __gen_01_loopDelaySamples_194_value * 0.002);
            number loopDelayChange_917 = (__gen_01_loopDelayFade_196_value >= 1) * (rnbo_abs(desiredLoopDelaySamples_297 - __gen_01_loopDelaySamples_194_value) > loopDelayTolerance_916);
            number oldLoopDelay_918 = ((bool)(loopDelayChange_917) ? __gen_01_loopDelaySamples_194_value : __gen_01_previousLoopDelaySamples_195_value);
            number newLoopDelay_919 = ((bool)(loopDelayChange_917) ? desiredLoopDelaySamples_297 : __gen_01_loopDelaySamples_194_value);
            number delayFadePhase_920 = ((bool)(loopDelayChange_917) ? 0 : __gen_01_loopDelayFade_196_value);
            auto delayFadeSamples_921 = this->maximum(16, this->sr * 0.03);

            auto nextDelayFade_922 = this->minimum(
                1,
                delayFadePhase_920 + ((delayFadeSamples_921 == 0. ? 0. : (number)1 / delayFadeSamples_921))
            );

            __gen_01_previousLoopDelaySamples_195_value = oldLoopDelay_918;
            __gen_01_loopDelaySamples_194_value = newLoopDelay_919;
            __gen_01_loopDelayFade_196_value = nextDelayFade_922;
            number oldReturnL_923 = this->gen_01_feedbackL_74_read(oldLoopDelay_918, 0);
            number oldReturnR_924 = this->gen_01_feedbackR_75_read(oldLoopDelay_918, 0);
            number newReturnL_925 = this->gen_01_feedbackL_74_read(newLoopDelay_919, 0);
            number newReturnR_926 = this->gen_01_feedbackR_75_read(newLoopDelay_919, 0);
            number oldTapGain_927 = rnbo_cos(delayFadePhase_920 * 3.14159265358979323846 * 0.5);
            number newTapGain_928 = rnbo_sin(delayFadePhase_920 * 3.14159265358979323846 * 0.5);
            __gen_01_feedbackAge_197_value = ((bool)(resetNow_233) ? 0 : this->minimum(4194304, __gen_01_feedbackAge_197_value + 1));
            number feedbackPrimed_929 = __gen_01_feedbackAge_197_value >= this->maximum(oldLoopDelay_918, newLoopDelay_919);
            number returnL_930 = (oldReturnL_923 * oldTapGain_927 + newReturnL_925 * newTapGain_928) * feedbackPrimed_929;
            number returnR_931 = (oldReturnR_924 * oldTapGain_927 + newReturnR_926 * newTapGain_928) * feedbackPrimed_929;
            auto fbUnity_932 = this->minimum(fb_207, 1);
            number injectionGain_933 = (this->maximum(0, 1 - fbUnity_932 * fbUnity_932) <= 0 ? 0 : rnbo_sqrt(this->maximum(0, 1 - fbUnity_932 * fbUnity_932)));
            number loopL_934 = patternGrainL_914 * injectionGain_933 + returnL_930 * fb_207;
            number loopR_935 = patternGrainR_915 * injectionGain_933 + returnR_931 * fb_207;
            number safeL_936 = (this->maximum(1, rnbo_abs(loopL_934) / (number)0.98) == 0. ? 0. : loopL_934 / this->maximum(1, rnbo_abs(loopL_934) / (number)0.98));
            number safeR_937 = (this->maximum(1, rnbo_abs(loopR_935) / (number)0.98) == 0. ? 0. : loopR_935 / this->maximum(1, rnbo_abs(loopR_935) / (number)0.98));
            this->gen_01_feedbackL_74_write((clearActive_235 == 0 ? safeL_936 : 0));
            this->gen_01_feedbackR_75_write((clearActive_235 == 0 ? safeR_937 : 0));
            number wetL_938 = (patternGrainL_914 + auditionL_460 + returnL_930 * fb_207) * clearGain_236;
            number wetR_939 = (patternGrainR_915 + auditionR_462 + returnR_931 * fb_207) * clearGain_236;
            number dryGain_940 = rnbo_cos(wet_213 * 3.14159265358979323846 * 0.5);
            number wetGain_941 = rnbo_sin(wet_213 * 3.14159265358979323846 * 0.5);
            number outputL_942 = inputL_13 * dryGain_940 + wetL_938 * wetGain_941;
            number outputR_943 = inputR_14 * dryGain_940 + wetR_939 * wetGain_941;
            number stepEvent_944 = ((bool)(clockTrig_305) ? rotatedStep_318 + 1 : 0);
            number grainEvent_945 = ((bool)(auditionValid_410) ? auditionRequest_251 : ((bool)(playHit_409) ? deferredCursor_355 + 1 : 0));

            {
                ScatterloomDSP_0 = (this->maximum(1, rnbo_abs(outputL_942)) == 0. ? 0. : outputL_942 / this->maximum(1, rnbo_abs(outputL_942)));
                ScatterloomDSP_1 = (this->maximum(1, rnbo_abs(outputR_943)) == 0. ? 0. : outputR_943 / this->maximum(1, rnbo_abs(outputR_943)));
                ScatterloomDSP_2 = onset_243;

                if (onset_243 > 0.5) ::scatterloomPushEvent(ScatterloomEventType::capture, 0);
                ScatterloomDSP_3 = __gen_01_visualSlot_174_value;
                ScatterloomDSP_4 = effectiveRotation_316;

                this->scatterloomEffectiveRotation = effectiveRotation_316;
                ScatterloomDSP_5 = effectiveSensitivity_226 * 100;

                this->scatterloomEffectiveSensitivity = effectiveSensitivity_226 * 100;
                ScatterloomDSP_6 = __gen_01_poolCount_85_value;

                this->scatterloomPoolCount = __gen_01_poolCount_85_value;
                ScatterloomDSP_7 = clearActive_235;

                this->scatterloomClearActive = clearActive_235;
                ScatterloomDSP_8 = __gen_01_visualStep_176_value;

                this->scatterloomCurrentStep = __gen_01_visualStep_176_value;
                ScatterloomDSP_9 = stepEvent_944;

                if (stepEvent_944 > 0.5) ::scatterloomPushEvent(ScatterloomEventType::step, (int)(stepEvent_944 - 1));
                ScatterloomDSP_10 = grainEvent_945;

                if (grainEvent_945 > 0.5) { ::scatterloomPushGrainEvent((int)(grainEvent_945), (int)((bool)(auditionValid_410) ? auditionSelectedSlot : selectedSlot)); if (!(bool)(auditionValid_410)) ::scatterloomPushTransitionEvent((int)(grainEvent_945), (int)(nextGrainCursor_417 + 1)); }
                ScatterloomDSP_11 = clockEnabled_302;

                this->scatterloomTransportRunning = clockEnabled_302;
                ScatterloomDSP_12 = detectedOnset_242;

                if (detectedOnset_242 > 0.5) ::scatterloomPushEvent(ScatterloomEventType::detection, 0);
            }
        }

        number expr_98 = 0;
        number expr_99 = 0;
        number expr_100 = 0;
        number expr_101 = 0;
        number expr_102 = 0;
        number expr_103 = 0;
        number expr_104 = 0;
        number expr_105 = 0;
        number expr_106 = 0;
        number expr_107 = 0;
        number expr_108 = 0;
        number expr_109 = 0;
        expr_98 = ScatterloomDSP_0, expr_99 = ScatterloomDSP_1, expr_100 = ScatterloomDSP_2, expr_101 = ScatterloomDSP_3, expr_102 = ScatterloomDSP_4, expr_103 = ScatterloomDSP_5, expr_104 = ScatterloomDSP_6, expr_105 = ScatterloomDSP_7, expr_106 = ScatterloomDSP_8, expr_107 = ScatterloomDSP_9, expr_108 = ScatterloomDSP_10, expr_109 = ScatterloomDSP_11;
        out4[(Index)i] = expr_101;
        out1[(Index)i] = expr_98;
        out9[(Index)i] = expr_106;
        out7[(Index)i] = expr_104;
        out12[(Index)i] = expr_109;
        out10[(Index)i] = expr_107;
        out8[(Index)i] = expr_105;
        out6[(Index)i] = expr_103;
        out11[(Index)i] = expr_108;
        out2[(Index)i] = expr_99;
        out3[(Index)i] = expr_100;
        out5[(Index)i] = expr_102;
        this->gen_01_feedbackR_75_step();
        this->gen_01_feedbackL_74_step();
        this->gen_01_triggerDelay_73_step();
        this->gen_01_preR_72_step();
        this->gen_01_preL_71_step();
    }

    this->gen_01_fastEnv_76_value = __gen_01_fastEnv_76_value;
    this->gen_01_slowEnv_77_value = __gen_01_slowEnv_77_value;
    this->gen_01_levelEnv_78_value = __gen_01_levelEnv_78_value;
    this->gen_01_activityEnv_79_value = __gen_01_activityEnv_79_value;
    this->gen_01_adaptiveThreshold_80_value = __gen_01_adaptiveThreshold_80_value;
    this->gen_01_previousClear_173_value = __gen_01_previousClear_173_value;
    this->gen_01_clearCountdown_171_value = __gen_01_clearCountdown_171_value;
    this->gen_01_clearFlushRemaining_172_value = __gen_01_clearFlushRemaining_172_value;
    this->gen_01_cooldown_81_value = __gen_01_cooldown_81_value;
    this->gen_01_onsetArmed_82_value = __gen_01_onsetArmed_82_value;
    this->gen_01_rearmCounter_83_value = __gen_01_rearmCounter_83_value;
    this->gen_01_captureSlot_84_value = __gen_01_captureSlot_84_value;
    this->gen_01_previousRemoveRequest_182_value = __gen_01_previousRemoveRequest_182_value;
    this->gen_01_previousAuditionRequest_183_value = __gen_01_previousAuditionRequest_183_value;
    this->gen_01_previousReorderCommit_184_value = __gen_01_previousReorderCommit_184_value;
    this->gen_01_poolCount_85_value = __gen_01_poolCount_85_value;
    this->gen_01_pendingReorder_185_value = __gen_01_pendingReorder_185_value;
    this->gen_01_pendingReorderFrom_186_value = __gen_01_pendingReorderFrom_186_value;
    this->gen_01_pendingReorderTo_187_value = __gen_01_pendingReorderTo_187_value;
    this->gen_01_lastSamplesPerBeat_170_value = __gen_01_lastSamplesPerBeat_170_value;
    this->gen_01_previousHostRunning_169_value = __gen_01_previousHostRunning_169_value;
    this->gen_01_clockPhase_86_value = __gen_01_clockPhase_86_value;
    this->gen_01_rotationBeatPhase_94_value = __gen_01_rotationBeatPhase_94_value;
    this->gen_01_rotationRandomState_95_value = __gen_01_rotationRandomState_95_value;
    this->gen_01_rotationOffset_93_value = __gen_01_rotationOffset_93_value;
    this->gen_01_stepIndex_87_value = __gen_01_stepIndex_87_value;
    this->gen_01_grainStartSchedule_181_value = __gen_01_grainStartSchedule_181_value;
    this->gen_01_transportRunSamples_179_value = __gen_01_transportRunSamples_179_value;
    this->gen_01_previousDelayedGate_180_value = __gen_01_previousDelayedGate_180_value;
    this->gen_01_timingPhaseReady_178_value = __gen_01_timingPhaseReady_178_value;
    this->gen_01_previousTimingPhase_177_value = __gen_01_previousTimingPhase_177_value;
    this->gen_01_visualStep_176_value = __gen_01_visualStep_176_value;
    this->gen_01_previousSelectionMode_90_value = __gen_01_previousSelectionMode_90_value;
    this->gen_01_grainCursor_88_value = __gen_01_grainCursor_88_value;
    this->gen_01_deferNewest_96_value = __gen_01_deferNewest_96_value;
    this->gen_01_grainRandomState_89_value = __gen_01_grainRandomState_89_value;
    this->gen_01_previousMarkovCommit_91_value = __gen_01_previousMarkovCommit_91_value;
    this->gen_01_markovActiveBank_92_value = __gen_01_markovActiveBank_92_value;
    this->gen_01_visualCountdown_175_value = __gen_01_visualCountdown_175_value;
    this->gen_01_visualSlot_174_value = __gen_01_visualSlot_174_value;
    this->gen_01_auditionSlot_188_value = __gen_01_auditionSlot_188_value;
    this->gen_01_auditionPosition_189_value = __gen_01_auditionPosition_189_value;
    this->gen_01_auditionBody_190_value = __gen_01_auditionBody_190_value;
    this->gen_01_auditionAttack_191_value = __gen_01_auditionAttack_191_value;
    this->gen_01_auditionLevel_192_value = __gen_01_auditionLevel_192_value;
    this->gen_01_auditionStart_193_value = __gen_01_auditionStart_193_value;
    this->gen_01_randomState_162_value = __gen_01_randomState_162_value;
    this->gen_01_voiceLevel0_102_value = __gen_01_voiceLevel0_102_value;
    this->gen_01_voiceAttack0_101_value = __gen_01_voiceAttack0_101_value;
    this->gen_01_voiceBody0_100_value = __gen_01_voiceBody0_100_value;
    this->gen_01_voicePos0_99_value = __gen_01_voicePos0_99_value;
    this->gen_01_voiceLevel1_108_value = __gen_01_voiceLevel1_108_value;
    this->gen_01_voiceAttack1_107_value = __gen_01_voiceAttack1_107_value;
    this->gen_01_voiceBody1_106_value = __gen_01_voiceBody1_106_value;
    this->gen_01_voicePos1_105_value = __gen_01_voicePos1_105_value;
    this->gen_01_voiceLevel2_114_value = __gen_01_voiceLevel2_114_value;
    this->gen_01_voiceAttack2_113_value = __gen_01_voiceAttack2_113_value;
    this->gen_01_voiceBody2_112_value = __gen_01_voiceBody2_112_value;
    this->gen_01_voicePos2_111_value = __gen_01_voicePos2_111_value;
    this->gen_01_voiceLevel3_120_value = __gen_01_voiceLevel3_120_value;
    this->gen_01_voiceAttack3_119_value = __gen_01_voiceAttack3_119_value;
    this->gen_01_voiceBody3_118_value = __gen_01_voiceBody3_118_value;
    this->gen_01_voicePos3_117_value = __gen_01_voicePos3_117_value;
    this->gen_01_voiceLevel4_126_value = __gen_01_voiceLevel4_126_value;
    this->gen_01_voiceAttack4_125_value = __gen_01_voiceAttack4_125_value;
    this->gen_01_voiceBody4_124_value = __gen_01_voiceBody4_124_value;
    this->gen_01_voicePos4_123_value = __gen_01_voicePos4_123_value;
    this->gen_01_voiceLevel5_132_value = __gen_01_voiceLevel5_132_value;
    this->gen_01_voiceAttack5_131_value = __gen_01_voiceAttack5_131_value;
    this->gen_01_voiceBody5_130_value = __gen_01_voiceBody5_130_value;
    this->gen_01_voicePos5_129_value = __gen_01_voicePos5_129_value;
    this->gen_01_voiceLevel6_138_value = __gen_01_voiceLevel6_138_value;
    this->gen_01_voiceAttack6_137_value = __gen_01_voiceAttack6_137_value;
    this->gen_01_voiceBody6_136_value = __gen_01_voiceBody6_136_value;
    this->gen_01_voicePos6_135_value = __gen_01_voicePos6_135_value;
    this->gen_01_voiceLevel7_144_value = __gen_01_voiceLevel7_144_value;
    this->gen_01_voiceAttack7_143_value = __gen_01_voiceAttack7_143_value;
    this->gen_01_voiceBody7_142_value = __gen_01_voiceBody7_142_value;
    this->gen_01_voicePos7_141_value = __gen_01_voicePos7_141_value;
    this->gen_01_nextVoice_97_value = __gen_01_nextVoice_97_value;
    this->gen_01_voiceSlot0_98_value = __gen_01_voiceSlot0_98_value;
    this->gen_01_voiceSlot1_104_value = __gen_01_voiceSlot1_104_value;
    this->gen_01_voiceSlot2_110_value = __gen_01_voiceSlot2_110_value;
    this->gen_01_voiceSlot3_116_value = __gen_01_voiceSlot3_116_value;
    this->gen_01_voiceSlot4_122_value = __gen_01_voiceSlot4_122_value;
    this->gen_01_voiceSlot5_128_value = __gen_01_voiceSlot5_128_value;
    this->gen_01_voiceSlot6_134_value = __gen_01_voiceSlot6_134_value;
    this->gen_01_voiceSlot7_140_value = __gen_01_voiceSlot7_140_value;
    this->gen_01_voiceReverse0_103_value = __gen_01_voiceReverse0_103_value;
    this->gen_01_voiceReverse1_109_value = __gen_01_voiceReverse1_109_value;
    this->gen_01_voiceReverse2_115_value = __gen_01_voiceReverse2_115_value;
    this->gen_01_voiceReverse3_121_value = __gen_01_voiceReverse3_121_value;
    this->gen_01_voiceReverse4_127_value = __gen_01_voiceReverse4_127_value;
    this->gen_01_voiceReverse5_133_value = __gen_01_voiceReverse5_133_value;
    this->gen_01_voiceReverse6_139_value = __gen_01_voiceReverse6_139_value;
    this->gen_01_voiceReverse7_145_value = __gen_01_voiceReverse7_145_value;
    this->gen_01_voicePan0_146_value = __gen_01_voicePan0_146_value;
    this->gen_01_voicePan1_147_value = __gen_01_voicePan1_147_value;
    this->gen_01_voicePan2_148_value = __gen_01_voicePan2_148_value;
    this->gen_01_voicePan3_149_value = __gen_01_voicePan3_149_value;
    this->gen_01_voicePan4_150_value = __gen_01_voicePan4_150_value;
    this->gen_01_voicePan5_151_value = __gen_01_voicePan5_151_value;
    this->gen_01_voicePan6_152_value = __gen_01_voicePan6_152_value;
    this->gen_01_voicePan7_153_value = __gen_01_voicePan7_153_value;
    this->gen_01_voiceStart0_154_value = __gen_01_voiceStart0_154_value;
    this->gen_01_voiceStart1_155_value = __gen_01_voiceStart1_155_value;
    this->gen_01_voiceStart2_156_value = __gen_01_voiceStart2_156_value;
    this->gen_01_voiceStart3_157_value = __gen_01_voiceStart3_157_value;
    this->gen_01_voiceStart4_158_value = __gen_01_voiceStart4_158_value;
    this->gen_01_voiceStart5_159_value = __gen_01_voiceStart5_159_value;
    this->gen_01_voiceStart6_160_value = __gen_01_voiceStart6_160_value;
    this->gen_01_voiceStart7_161_value = __gen_01_voiceStart7_161_value;
    this->gen_01_stealSlot_163_value = __gen_01_stealSlot_163_value;
    this->gen_01_stealPosition_164_value = __gen_01_stealPosition_164_value;
    this->gen_01_stealDirection_165_value = __gen_01_stealDirection_165_value;
    this->gen_01_stealPan_168_value = __gen_01_stealPan_168_value;
    this->gen_01_stealInitialGain_166_value = __gen_01_stealInitialGain_166_value;
    this->gen_01_stealFadePosition_167_value = __gen_01_stealFadePosition_167_value;
    this->gen_01_loopDelaySamples_194_value = __gen_01_loopDelaySamples_194_value;
    this->gen_01_loopDelayFade_196_value = __gen_01_loopDelayFade_196_value;
    this->gen_01_previousLoopDelaySamples_195_value = __gen_01_previousLoopDelaySamples_195_value;
    this->gen_01_feedbackAge_197_value = __gen_01_feedbackAge_197_value;
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

number gen_01_slide_198_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_198_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(1600)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1600)));
    this->gen_01_slide_198_prev = this->gen_01_slide_198_prev + ((x > this->gen_01_slide_198_prev ? iup : idown)) * temp;
    return this->gen_01_slide_198_prev;
}

void gen_01_slide_198_reset() {
    this->gen_01_slide_198_prev = 0;
}

number gen_01_slide_200_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_200_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(2200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(2200)));
    this->gen_01_slide_200_prev = this->gen_01_slide_200_prev + ((x > this->gen_01_slide_200_prev ? iup : idown)) * temp;
    return this->gen_01_slide_200_prev;
}

void gen_01_slide_200_reset() {
    this->gen_01_slide_200_prev = 0;
}

number gen_01_slide_202_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_202_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    this->gen_01_slide_202_prev = this->gen_01_slide_202_prev + ((x > this->gen_01_slide_202_prev ? iup : idown)) * temp;
    return this->gen_01_slide_202_prev;
}

void gen_01_slide_202_reset() {
    this->gen_01_slide_202_prev = 0;
}

number gen_01_slide_204_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_204_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    this->gen_01_slide_204_prev = this->gen_01_slide_204_prev + ((x > this->gen_01_slide_204_prev ? iup : idown)) * temp;
    return this->gen_01_slide_204_prev;
}

void gen_01_slide_204_reset() {
    this->gen_01_slide_204_prev = 0;
}

number gen_01_slide_206_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_206_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(3000)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(3000)));
    this->gen_01_slide_206_prev = this->gen_01_slide_206_prev + ((x > this->gen_01_slide_206_prev ? iup : idown)) * temp;
    return this->gen_01_slide_206_prev;
}

void gen_01_slide_206_reset() {
    this->gen_01_slide_206_prev = 0;
}

number gen_01_slide_208_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_208_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    this->gen_01_slide_208_prev = this->gen_01_slide_208_prev + ((x > this->gen_01_slide_208_prev ? iup : idown)) * temp;
    return this->gen_01_slide_208_prev;
}

void gen_01_slide_208_reset() {
    this->gen_01_slide_208_prev = 0;
}

number gen_01_slide_210_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_210_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    this->gen_01_slide_210_prev = this->gen_01_slide_210_prev + ((x > this->gen_01_slide_210_prev ? iup : idown)) * temp;
    return this->gen_01_slide_210_prev;
}

void gen_01_slide_210_reset() {
    this->gen_01_slide_210_prev = 0;
}

number gen_01_slide_212_next(number x, number up, number down) {
    RNBO_UNUSED(down);
    RNBO_UNUSED(up);
    number temp = x - this->gen_01_slide_212_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1200)));
    this->gen_01_slide_212_prev = this->gen_01_slide_212_prev + ((x > this->gen_01_slide_212_prev ? iup : idown)) * temp;
    return this->gen_01_slide_212_prev;
}

void gen_01_slide_212_reset() {
    this->gen_01_slide_212_prev = 0;
}

number gen_01_feedbackAge_197_getvalue() {
    return this->gen_01_feedbackAge_197_value;
}

void gen_01_feedbackAge_197_setvalue(number val) {
    this->gen_01_feedbackAge_197_value = val;
}

void gen_01_feedbackAge_197_reset() {
    this->gen_01_feedbackAge_197_value = 0;
}

void gen_01_feedbackAge_197_init() {
    this->gen_01_feedbackAge_197_value = 4194304;
}

number gen_01_loopDelayFade_196_getvalue() {
    return this->gen_01_loopDelayFade_196_value;
}

void gen_01_loopDelayFade_196_setvalue(number val) {
    this->gen_01_loopDelayFade_196_value = val;
}

void gen_01_loopDelayFade_196_reset() {
    this->gen_01_loopDelayFade_196_value = 0;
}

void gen_01_loopDelayFade_196_init() {
    this->gen_01_loopDelayFade_196_value = 1;
}

number gen_01_previousLoopDelaySamples_195_getvalue() {
    return this->gen_01_previousLoopDelaySamples_195_value;
}

void gen_01_previousLoopDelaySamples_195_setvalue(number val) {
    this->gen_01_previousLoopDelaySamples_195_value = val;
}

void gen_01_previousLoopDelaySamples_195_reset() {
    this->gen_01_previousLoopDelaySamples_195_value = 0;
}

void gen_01_previousLoopDelaySamples_195_init() {
    this->gen_01_previousLoopDelaySamples_195_value = 24000;
}

number gen_01_loopDelaySamples_194_getvalue() {
    return this->gen_01_loopDelaySamples_194_value;
}

void gen_01_loopDelaySamples_194_setvalue(number val) {
    this->gen_01_loopDelaySamples_194_value = val;
}

void gen_01_loopDelaySamples_194_reset() {
    this->gen_01_loopDelaySamples_194_value = 0;
}

void gen_01_loopDelaySamples_194_init() {
    this->gen_01_loopDelaySamples_194_value = 24000;
}

number gen_01_auditionStart_193_getvalue() {
    return this->gen_01_auditionStart_193_value;
}

void gen_01_auditionStart_193_setvalue(number val) {
    this->gen_01_auditionStart_193_value = val;
}

void gen_01_auditionStart_193_reset() {
    this->gen_01_auditionStart_193_value = 0;
}

void gen_01_auditionStart_193_init() {
    this->gen_01_auditionStart_193_value = 0;
}

number gen_01_auditionLevel_192_getvalue() {
    return this->gen_01_auditionLevel_192_value;
}

void gen_01_auditionLevel_192_setvalue(number val) {
    this->gen_01_auditionLevel_192_value = val;
}

void gen_01_auditionLevel_192_reset() {
    this->gen_01_auditionLevel_192_value = 0;
}

void gen_01_auditionLevel_192_init() {
    this->gen_01_auditionLevel_192_value = 0;
}

number gen_01_auditionAttack_191_getvalue() {
    return this->gen_01_auditionAttack_191_value;
}

void gen_01_auditionAttack_191_setvalue(number val) {
    this->gen_01_auditionAttack_191_value = val;
}

void gen_01_auditionAttack_191_reset() {
    this->gen_01_auditionAttack_191_value = 0;
}

void gen_01_auditionAttack_191_init() {
    this->gen_01_auditionAttack_191_value = 144;
}

number gen_01_auditionBody_190_getvalue() {
    return this->gen_01_auditionBody_190_value;
}

void gen_01_auditionBody_190_setvalue(number val) {
    this->gen_01_auditionBody_190_value = val;
}

void gen_01_auditionBody_190_reset() {
    this->gen_01_auditionBody_190_value = 0;
}

void gen_01_auditionBody_190_init() {
    this->gen_01_auditionBody_190_value = 9600;
}

number gen_01_auditionPosition_189_getvalue() {
    return this->gen_01_auditionPosition_189_value;
}

void gen_01_auditionPosition_189_setvalue(number val) {
    this->gen_01_auditionPosition_189_value = val;
}

void gen_01_auditionPosition_189_reset() {
    this->gen_01_auditionPosition_189_value = 0;
}

void gen_01_auditionPosition_189_init() {
    this->gen_01_auditionPosition_189_value = 1048576;
}

number gen_01_auditionSlot_188_getvalue() {
    return this->gen_01_auditionSlot_188_value;
}

void gen_01_auditionSlot_188_setvalue(number val) {
    this->gen_01_auditionSlot_188_value = val;
}

void gen_01_auditionSlot_188_reset() {
    this->gen_01_auditionSlot_188_value = 0;
}

void gen_01_auditionSlot_188_init() {
    this->gen_01_auditionSlot_188_value = 0;
}

number gen_01_pendingReorderTo_187_getvalue() {
    return this->gen_01_pendingReorderTo_187_value;
}

void gen_01_pendingReorderTo_187_setvalue(number val) {
    this->gen_01_pendingReorderTo_187_value = val;
}

void gen_01_pendingReorderTo_187_reset() {
    this->gen_01_pendingReorderTo_187_value = 0;
}

void gen_01_pendingReorderTo_187_init() {
    this->gen_01_pendingReorderTo_187_value = 0;
}

number gen_01_pendingReorderFrom_186_getvalue() {
    return this->gen_01_pendingReorderFrom_186_value;
}

void gen_01_pendingReorderFrom_186_setvalue(number val) {
    this->gen_01_pendingReorderFrom_186_value = val;
}

void gen_01_pendingReorderFrom_186_reset() {
    this->gen_01_pendingReorderFrom_186_value = 0;
}

void gen_01_pendingReorderFrom_186_init() {
    this->gen_01_pendingReorderFrom_186_value = 0;
}

number gen_01_pendingReorder_185_getvalue() {
    return this->gen_01_pendingReorder_185_value;
}

void gen_01_pendingReorder_185_setvalue(number val) {
    this->gen_01_pendingReorder_185_value = val;
}

void gen_01_pendingReorder_185_reset() {
    this->gen_01_pendingReorder_185_value = 0;
}

void gen_01_pendingReorder_185_init() {
    this->gen_01_pendingReorder_185_value = 0;
}

number gen_01_previousReorderCommit_184_getvalue() {
    return this->gen_01_previousReorderCommit_184_value;
}

void gen_01_previousReorderCommit_184_setvalue(number val) {
    this->gen_01_previousReorderCommit_184_value = val;
}

void gen_01_previousReorderCommit_184_reset() {
    this->gen_01_previousReorderCommit_184_value = 0;
}

void gen_01_previousReorderCommit_184_init() {
    this->gen_01_previousReorderCommit_184_value = 0;
}

number gen_01_previousAuditionRequest_183_getvalue() {
    return this->gen_01_previousAuditionRequest_183_value;
}

void gen_01_previousAuditionRequest_183_setvalue(number val) {
    this->gen_01_previousAuditionRequest_183_value = val;
}

void gen_01_previousAuditionRequest_183_reset() {
    this->gen_01_previousAuditionRequest_183_value = 0;
}

void gen_01_previousAuditionRequest_183_init() {
    this->gen_01_previousAuditionRequest_183_value = 0;
}

number gen_01_previousRemoveRequest_182_getvalue() {
    return this->gen_01_previousRemoveRequest_182_value;
}

void gen_01_previousRemoveRequest_182_setvalue(number val) {
    this->gen_01_previousRemoveRequest_182_value = val;
}

void gen_01_previousRemoveRequest_182_reset() {
    this->gen_01_previousRemoveRequest_182_value = 0;
}

void gen_01_previousRemoveRequest_182_init() {
    this->gen_01_previousRemoveRequest_182_value = 0;
}

number gen_01_grainStartSchedule_181_getvalue() {
    return this->gen_01_grainStartSchedule_181_value;
}

void gen_01_grainStartSchedule_181_setvalue(number val) {
    this->gen_01_grainStartSchedule_181_value = val;
}

void gen_01_grainStartSchedule_181_reset() {
    this->gen_01_grainStartSchedule_181_value = 0;
}

void gen_01_grainStartSchedule_181_init() {
    this->gen_01_grainStartSchedule_181_value = 0;
}

number gen_01_previousDelayedGate_180_getvalue() {
    return this->gen_01_previousDelayedGate_180_value;
}

void gen_01_previousDelayedGate_180_setvalue(number val) {
    this->gen_01_previousDelayedGate_180_value = val;
}

void gen_01_previousDelayedGate_180_reset() {
    this->gen_01_previousDelayedGate_180_value = 0;
}

void gen_01_previousDelayedGate_180_init() {
    this->gen_01_previousDelayedGate_180_value = 0;
}

number gen_01_transportRunSamples_179_getvalue() {
    return this->gen_01_transportRunSamples_179_value;
}

void gen_01_transportRunSamples_179_setvalue(number val) {
    this->gen_01_transportRunSamples_179_value = val;
}

void gen_01_transportRunSamples_179_reset() {
    this->gen_01_transportRunSamples_179_value = 0;
}

void gen_01_transportRunSamples_179_init() {
    this->gen_01_transportRunSamples_179_value = 0;
}

number gen_01_timingPhaseReady_178_getvalue() {
    return this->gen_01_timingPhaseReady_178_value;
}

void gen_01_timingPhaseReady_178_setvalue(number val) {
    this->gen_01_timingPhaseReady_178_value = val;
}

void gen_01_timingPhaseReady_178_reset() {
    this->gen_01_timingPhaseReady_178_value = 0;
}

void gen_01_timingPhaseReady_178_init() {
    this->gen_01_timingPhaseReady_178_value = 0;
}

number gen_01_previousTimingPhase_177_getvalue() {
    return this->gen_01_previousTimingPhase_177_value;
}

void gen_01_previousTimingPhase_177_setvalue(number val) {
    this->gen_01_previousTimingPhase_177_value = val;
}

void gen_01_previousTimingPhase_177_reset() {
    this->gen_01_previousTimingPhase_177_value = 0;
}

void gen_01_previousTimingPhase_177_init() {
    this->gen_01_previousTimingPhase_177_value = 0;
}

number gen_01_visualStep_176_getvalue() {
    return this->gen_01_visualStep_176_value;
}

void gen_01_visualStep_176_setvalue(number val) {
    this->gen_01_visualStep_176_value = val;
}

void gen_01_visualStep_176_reset() {
    this->gen_01_visualStep_176_value = 0;
}

void gen_01_visualStep_176_init() {
    this->gen_01_visualStep_176_value = 0;
}

number gen_01_visualCountdown_175_getvalue() {
    return this->gen_01_visualCountdown_175_value;
}

void gen_01_visualCountdown_175_setvalue(number val) {
    this->gen_01_visualCountdown_175_value = val;
}

void gen_01_visualCountdown_175_reset() {
    this->gen_01_visualCountdown_175_value = 0;
}

void gen_01_visualCountdown_175_init() {
    this->gen_01_visualCountdown_175_value = 0;
}

number gen_01_visualSlot_174_getvalue() {
    return this->gen_01_visualSlot_174_value;
}

void gen_01_visualSlot_174_setvalue(number val) {
    this->gen_01_visualSlot_174_value = val;
}

void gen_01_visualSlot_174_reset() {
    this->gen_01_visualSlot_174_value = 0;
}

void gen_01_visualSlot_174_init() {
    this->gen_01_visualSlot_174_value = 0;
}

number gen_01_previousClear_173_getvalue() {
    return this->gen_01_previousClear_173_value;
}

void gen_01_previousClear_173_setvalue(number val) {
    this->gen_01_previousClear_173_value = val;
}

void gen_01_previousClear_173_reset() {
    this->gen_01_previousClear_173_value = 0;
}

void gen_01_previousClear_173_init() {
    this->gen_01_previousClear_173_value = 0;
}

number gen_01_clearFlushRemaining_172_getvalue() {
    return this->gen_01_clearFlushRemaining_172_value;
}

void gen_01_clearFlushRemaining_172_setvalue(number val) {
    this->gen_01_clearFlushRemaining_172_value = val;
}

void gen_01_clearFlushRemaining_172_reset() {
    this->gen_01_clearFlushRemaining_172_value = 0;
}

void gen_01_clearFlushRemaining_172_init() {
    this->gen_01_clearFlushRemaining_172_value = 0;
}

number gen_01_clearCountdown_171_getvalue() {
    return this->gen_01_clearCountdown_171_value;
}

void gen_01_clearCountdown_171_setvalue(number val) {
    this->gen_01_clearCountdown_171_value = val;
}

void gen_01_clearCountdown_171_reset() {
    this->gen_01_clearCountdown_171_value = 0;
}

void gen_01_clearCountdown_171_init() {
    this->gen_01_clearCountdown_171_value = 0;
}

number gen_01_lastSamplesPerBeat_170_getvalue() {
    return this->gen_01_lastSamplesPerBeat_170_value;
}

void gen_01_lastSamplesPerBeat_170_setvalue(number val) {
    this->gen_01_lastSamplesPerBeat_170_value = val;
}

void gen_01_lastSamplesPerBeat_170_reset() {
    this->gen_01_lastSamplesPerBeat_170_value = 0;
}

void gen_01_lastSamplesPerBeat_170_init() {
    this->gen_01_lastSamplesPerBeat_170_value = 24000;
}

number gen_01_previousHostRunning_169_getvalue() {
    return this->gen_01_previousHostRunning_169_value;
}

void gen_01_previousHostRunning_169_setvalue(number val) {
    this->gen_01_previousHostRunning_169_value = val;
}

void gen_01_previousHostRunning_169_reset() {
    this->gen_01_previousHostRunning_169_value = 0;
}

void gen_01_previousHostRunning_169_init() {
    this->gen_01_previousHostRunning_169_value = 0;
}

number gen_01_stealPan_168_getvalue() {
    return this->gen_01_stealPan_168_value;
}

void gen_01_stealPan_168_setvalue(number val) {
    this->gen_01_stealPan_168_value = val;
}

void gen_01_stealPan_168_reset() {
    this->gen_01_stealPan_168_value = 0;
}

void gen_01_stealPan_168_init() {
    this->gen_01_stealPan_168_value = 0;
}

number gen_01_stealFadePosition_167_getvalue() {
    return this->gen_01_stealFadePosition_167_value;
}

void gen_01_stealFadePosition_167_setvalue(number val) {
    this->gen_01_stealFadePosition_167_value = val;
}

void gen_01_stealFadePosition_167_reset() {
    this->gen_01_stealFadePosition_167_value = 0;
}

void gen_01_stealFadePosition_167_init() {
    this->gen_01_stealFadePosition_167_value = 1048576;
}

number gen_01_stealInitialGain_166_getvalue() {
    return this->gen_01_stealInitialGain_166_value;
}

void gen_01_stealInitialGain_166_setvalue(number val) {
    this->gen_01_stealInitialGain_166_value = val;
}

void gen_01_stealInitialGain_166_reset() {
    this->gen_01_stealInitialGain_166_value = 0;
}

void gen_01_stealInitialGain_166_init() {
    this->gen_01_stealInitialGain_166_value = 0;
}

number gen_01_stealDirection_165_getvalue() {
    return this->gen_01_stealDirection_165_value;
}

void gen_01_stealDirection_165_setvalue(number val) {
    this->gen_01_stealDirection_165_value = val;
}

void gen_01_stealDirection_165_reset() {
    this->gen_01_stealDirection_165_value = 0;
}

void gen_01_stealDirection_165_init() {
    this->gen_01_stealDirection_165_value = 1;
}

number gen_01_stealPosition_164_getvalue() {
    return this->gen_01_stealPosition_164_value;
}

void gen_01_stealPosition_164_setvalue(number val) {
    this->gen_01_stealPosition_164_value = val;
}

void gen_01_stealPosition_164_reset() {
    this->gen_01_stealPosition_164_value = 0;
}

void gen_01_stealPosition_164_init() {
    this->gen_01_stealPosition_164_value = 1048576;
}

number gen_01_stealSlot_163_getvalue() {
    return this->gen_01_stealSlot_163_value;
}

void gen_01_stealSlot_163_setvalue(number val) {
    this->gen_01_stealSlot_163_value = val;
}

void gen_01_stealSlot_163_reset() {
    this->gen_01_stealSlot_163_value = 0;
}

void gen_01_stealSlot_163_init() {
    this->gen_01_stealSlot_163_value = 0;
}

number gen_01_randomState_162_getvalue() {
    return this->gen_01_randomState_162_value;
}

void gen_01_randomState_162_setvalue(number val) {
    this->gen_01_randomState_162_value = val;
}

void gen_01_randomState_162_reset() {
    this->gen_01_randomState_162_value = 0;
}

void gen_01_randomState_162_init() {
    this->gen_01_randomState_162_value = 0.371;
}

number gen_01_voiceStart7_161_getvalue() {
    return this->gen_01_voiceStart7_161_value;
}

void gen_01_voiceStart7_161_setvalue(number val) {
    this->gen_01_voiceStart7_161_value = val;
}

void gen_01_voiceStart7_161_reset() {
    this->gen_01_voiceStart7_161_value = 0;
}

void gen_01_voiceStart7_161_init() {
    this->gen_01_voiceStart7_161_value = 0;
}

number gen_01_voiceStart6_160_getvalue() {
    return this->gen_01_voiceStart6_160_value;
}

void gen_01_voiceStart6_160_setvalue(number val) {
    this->gen_01_voiceStart6_160_value = val;
}

void gen_01_voiceStart6_160_reset() {
    this->gen_01_voiceStart6_160_value = 0;
}

void gen_01_voiceStart6_160_init() {
    this->gen_01_voiceStart6_160_value = 0;
}

number gen_01_voiceStart5_159_getvalue() {
    return this->gen_01_voiceStart5_159_value;
}

void gen_01_voiceStart5_159_setvalue(number val) {
    this->gen_01_voiceStart5_159_value = val;
}

void gen_01_voiceStart5_159_reset() {
    this->gen_01_voiceStart5_159_value = 0;
}

void gen_01_voiceStart5_159_init() {
    this->gen_01_voiceStart5_159_value = 0;
}

number gen_01_voiceStart4_158_getvalue() {
    return this->gen_01_voiceStart4_158_value;
}

void gen_01_voiceStart4_158_setvalue(number val) {
    this->gen_01_voiceStart4_158_value = val;
}

void gen_01_voiceStart4_158_reset() {
    this->gen_01_voiceStart4_158_value = 0;
}

void gen_01_voiceStart4_158_init() {
    this->gen_01_voiceStart4_158_value = 0;
}

number gen_01_voiceStart3_157_getvalue() {
    return this->gen_01_voiceStart3_157_value;
}

void gen_01_voiceStart3_157_setvalue(number val) {
    this->gen_01_voiceStart3_157_value = val;
}

void gen_01_voiceStart3_157_reset() {
    this->gen_01_voiceStart3_157_value = 0;
}

void gen_01_voiceStart3_157_init() {
    this->gen_01_voiceStart3_157_value = 0;
}

number gen_01_voiceStart2_156_getvalue() {
    return this->gen_01_voiceStart2_156_value;
}

void gen_01_voiceStart2_156_setvalue(number val) {
    this->gen_01_voiceStart2_156_value = val;
}

void gen_01_voiceStart2_156_reset() {
    this->gen_01_voiceStart2_156_value = 0;
}

void gen_01_voiceStart2_156_init() {
    this->gen_01_voiceStart2_156_value = 0;
}

number gen_01_voiceStart1_155_getvalue() {
    return this->gen_01_voiceStart1_155_value;
}

void gen_01_voiceStart1_155_setvalue(number val) {
    this->gen_01_voiceStart1_155_value = val;
}

void gen_01_voiceStart1_155_reset() {
    this->gen_01_voiceStart1_155_value = 0;
}

void gen_01_voiceStart1_155_init() {
    this->gen_01_voiceStart1_155_value = 0;
}

number gen_01_voiceStart0_154_getvalue() {
    return this->gen_01_voiceStart0_154_value;
}

void gen_01_voiceStart0_154_setvalue(number val) {
    this->gen_01_voiceStart0_154_value = val;
}

void gen_01_voiceStart0_154_reset() {
    this->gen_01_voiceStart0_154_value = 0;
}

void gen_01_voiceStart0_154_init() {
    this->gen_01_voiceStart0_154_value = 0;
}

number gen_01_voicePan7_153_getvalue() {
    return this->gen_01_voicePan7_153_value;
}

void gen_01_voicePan7_153_setvalue(number val) {
    this->gen_01_voicePan7_153_value = val;
}

void gen_01_voicePan7_153_reset() {
    this->gen_01_voicePan7_153_value = 0;
}

void gen_01_voicePan7_153_init() {
    this->gen_01_voicePan7_153_value = 0;
}

number gen_01_voicePan6_152_getvalue() {
    return this->gen_01_voicePan6_152_value;
}

void gen_01_voicePan6_152_setvalue(number val) {
    this->gen_01_voicePan6_152_value = val;
}

void gen_01_voicePan6_152_reset() {
    this->gen_01_voicePan6_152_value = 0;
}

void gen_01_voicePan6_152_init() {
    this->gen_01_voicePan6_152_value = 0;
}

number gen_01_voicePan5_151_getvalue() {
    return this->gen_01_voicePan5_151_value;
}

void gen_01_voicePan5_151_setvalue(number val) {
    this->gen_01_voicePan5_151_value = val;
}

void gen_01_voicePan5_151_reset() {
    this->gen_01_voicePan5_151_value = 0;
}

void gen_01_voicePan5_151_init() {
    this->gen_01_voicePan5_151_value = 0;
}

number gen_01_voicePan4_150_getvalue() {
    return this->gen_01_voicePan4_150_value;
}

void gen_01_voicePan4_150_setvalue(number val) {
    this->gen_01_voicePan4_150_value = val;
}

void gen_01_voicePan4_150_reset() {
    this->gen_01_voicePan4_150_value = 0;
}

void gen_01_voicePan4_150_init() {
    this->gen_01_voicePan4_150_value = 0;
}

number gen_01_voicePan3_149_getvalue() {
    return this->gen_01_voicePan3_149_value;
}

void gen_01_voicePan3_149_setvalue(number val) {
    this->gen_01_voicePan3_149_value = val;
}

void gen_01_voicePan3_149_reset() {
    this->gen_01_voicePan3_149_value = 0;
}

void gen_01_voicePan3_149_init() {
    this->gen_01_voicePan3_149_value = 0;
}

number gen_01_voicePan2_148_getvalue() {
    return this->gen_01_voicePan2_148_value;
}

void gen_01_voicePan2_148_setvalue(number val) {
    this->gen_01_voicePan2_148_value = val;
}

void gen_01_voicePan2_148_reset() {
    this->gen_01_voicePan2_148_value = 0;
}

void gen_01_voicePan2_148_init() {
    this->gen_01_voicePan2_148_value = 0;
}

number gen_01_voicePan1_147_getvalue() {
    return this->gen_01_voicePan1_147_value;
}

void gen_01_voicePan1_147_setvalue(number val) {
    this->gen_01_voicePan1_147_value = val;
}

void gen_01_voicePan1_147_reset() {
    this->gen_01_voicePan1_147_value = 0;
}

void gen_01_voicePan1_147_init() {
    this->gen_01_voicePan1_147_value = 0;
}

number gen_01_voicePan0_146_getvalue() {
    return this->gen_01_voicePan0_146_value;
}

void gen_01_voicePan0_146_setvalue(number val) {
    this->gen_01_voicePan0_146_value = val;
}

void gen_01_voicePan0_146_reset() {
    this->gen_01_voicePan0_146_value = 0;
}

void gen_01_voicePan0_146_init() {
    this->gen_01_voicePan0_146_value = 0;
}

number gen_01_voiceReverse7_145_getvalue() {
    return this->gen_01_voiceReverse7_145_value;
}

void gen_01_voiceReverse7_145_setvalue(number val) {
    this->gen_01_voiceReverse7_145_value = val;
}

void gen_01_voiceReverse7_145_reset() {
    this->gen_01_voiceReverse7_145_value = 0;
}

void gen_01_voiceReverse7_145_init() {
    this->gen_01_voiceReverse7_145_value = 0;
}

number gen_01_voiceLevel7_144_getvalue() {
    return this->gen_01_voiceLevel7_144_value;
}

void gen_01_voiceLevel7_144_setvalue(number val) {
    this->gen_01_voiceLevel7_144_value = val;
}

void gen_01_voiceLevel7_144_reset() {
    this->gen_01_voiceLevel7_144_value = 0;
}

void gen_01_voiceLevel7_144_init() {
    this->gen_01_voiceLevel7_144_value = 0;
}

number gen_01_voiceAttack7_143_getvalue() {
    return this->gen_01_voiceAttack7_143_value;
}

void gen_01_voiceAttack7_143_setvalue(number val) {
    this->gen_01_voiceAttack7_143_value = val;
}

void gen_01_voiceAttack7_143_reset() {
    this->gen_01_voiceAttack7_143_value = 0;
}

void gen_01_voiceAttack7_143_init() {
    this->gen_01_voiceAttack7_143_value = 144;
}

number gen_01_voiceBody7_142_getvalue() {
    return this->gen_01_voiceBody7_142_value;
}

void gen_01_voiceBody7_142_setvalue(number val) {
    this->gen_01_voiceBody7_142_value = val;
}

void gen_01_voiceBody7_142_reset() {
    this->gen_01_voiceBody7_142_value = 0;
}

void gen_01_voiceBody7_142_init() {
    this->gen_01_voiceBody7_142_value = 9600;
}

number gen_01_voicePos7_141_getvalue() {
    return this->gen_01_voicePos7_141_value;
}

void gen_01_voicePos7_141_setvalue(number val) {
    this->gen_01_voicePos7_141_value = val;
}

void gen_01_voicePos7_141_reset() {
    this->gen_01_voicePos7_141_value = 0;
}

void gen_01_voicePos7_141_init() {
    this->gen_01_voicePos7_141_value = 1048576;
}

number gen_01_voiceSlot7_140_getvalue() {
    return this->gen_01_voiceSlot7_140_value;
}

void gen_01_voiceSlot7_140_setvalue(number val) {
    this->gen_01_voiceSlot7_140_value = val;
}

void gen_01_voiceSlot7_140_reset() {
    this->gen_01_voiceSlot7_140_value = 0;
}

void gen_01_voiceSlot7_140_init() {
    this->gen_01_voiceSlot7_140_value = 0;
}

number gen_01_voiceReverse6_139_getvalue() {
    return this->gen_01_voiceReverse6_139_value;
}

void gen_01_voiceReverse6_139_setvalue(number val) {
    this->gen_01_voiceReverse6_139_value = val;
}

void gen_01_voiceReverse6_139_reset() {
    this->gen_01_voiceReverse6_139_value = 0;
}

void gen_01_voiceReverse6_139_init() {
    this->gen_01_voiceReverse6_139_value = 0;
}

number gen_01_voiceLevel6_138_getvalue() {
    return this->gen_01_voiceLevel6_138_value;
}

void gen_01_voiceLevel6_138_setvalue(number val) {
    this->gen_01_voiceLevel6_138_value = val;
}

void gen_01_voiceLevel6_138_reset() {
    this->gen_01_voiceLevel6_138_value = 0;
}

void gen_01_voiceLevel6_138_init() {
    this->gen_01_voiceLevel6_138_value = 0;
}

number gen_01_voiceAttack6_137_getvalue() {
    return this->gen_01_voiceAttack6_137_value;
}

void gen_01_voiceAttack6_137_setvalue(number val) {
    this->gen_01_voiceAttack6_137_value = val;
}

void gen_01_voiceAttack6_137_reset() {
    this->gen_01_voiceAttack6_137_value = 0;
}

void gen_01_voiceAttack6_137_init() {
    this->gen_01_voiceAttack6_137_value = 144;
}

number gen_01_voiceBody6_136_getvalue() {
    return this->gen_01_voiceBody6_136_value;
}

void gen_01_voiceBody6_136_setvalue(number val) {
    this->gen_01_voiceBody6_136_value = val;
}

void gen_01_voiceBody6_136_reset() {
    this->gen_01_voiceBody6_136_value = 0;
}

void gen_01_voiceBody6_136_init() {
    this->gen_01_voiceBody6_136_value = 9600;
}

number gen_01_voicePos6_135_getvalue() {
    return this->gen_01_voicePos6_135_value;
}

void gen_01_voicePos6_135_setvalue(number val) {
    this->gen_01_voicePos6_135_value = val;
}

void gen_01_voicePos6_135_reset() {
    this->gen_01_voicePos6_135_value = 0;
}

void gen_01_voicePos6_135_init() {
    this->gen_01_voicePos6_135_value = 1048576;
}

number gen_01_voiceSlot6_134_getvalue() {
    return this->gen_01_voiceSlot6_134_value;
}

void gen_01_voiceSlot6_134_setvalue(number val) {
    this->gen_01_voiceSlot6_134_value = val;
}

void gen_01_voiceSlot6_134_reset() {
    this->gen_01_voiceSlot6_134_value = 0;
}

void gen_01_voiceSlot6_134_init() {
    this->gen_01_voiceSlot6_134_value = 0;
}

number gen_01_voiceReverse5_133_getvalue() {
    return this->gen_01_voiceReverse5_133_value;
}

void gen_01_voiceReverse5_133_setvalue(number val) {
    this->gen_01_voiceReverse5_133_value = val;
}

void gen_01_voiceReverse5_133_reset() {
    this->gen_01_voiceReverse5_133_value = 0;
}

void gen_01_voiceReverse5_133_init() {
    this->gen_01_voiceReverse5_133_value = 0;
}

number gen_01_voiceLevel5_132_getvalue() {
    return this->gen_01_voiceLevel5_132_value;
}

void gen_01_voiceLevel5_132_setvalue(number val) {
    this->gen_01_voiceLevel5_132_value = val;
}

void gen_01_voiceLevel5_132_reset() {
    this->gen_01_voiceLevel5_132_value = 0;
}

void gen_01_voiceLevel5_132_init() {
    this->gen_01_voiceLevel5_132_value = 0;
}

number gen_01_voiceAttack5_131_getvalue() {
    return this->gen_01_voiceAttack5_131_value;
}

void gen_01_voiceAttack5_131_setvalue(number val) {
    this->gen_01_voiceAttack5_131_value = val;
}

void gen_01_voiceAttack5_131_reset() {
    this->gen_01_voiceAttack5_131_value = 0;
}

void gen_01_voiceAttack5_131_init() {
    this->gen_01_voiceAttack5_131_value = 144;
}

number gen_01_voiceBody5_130_getvalue() {
    return this->gen_01_voiceBody5_130_value;
}

void gen_01_voiceBody5_130_setvalue(number val) {
    this->gen_01_voiceBody5_130_value = val;
}

void gen_01_voiceBody5_130_reset() {
    this->gen_01_voiceBody5_130_value = 0;
}

void gen_01_voiceBody5_130_init() {
    this->gen_01_voiceBody5_130_value = 9600;
}

number gen_01_voicePos5_129_getvalue() {
    return this->gen_01_voicePos5_129_value;
}

void gen_01_voicePos5_129_setvalue(number val) {
    this->gen_01_voicePos5_129_value = val;
}

void gen_01_voicePos5_129_reset() {
    this->gen_01_voicePos5_129_value = 0;
}

void gen_01_voicePos5_129_init() {
    this->gen_01_voicePos5_129_value = 1048576;
}

number gen_01_voiceSlot5_128_getvalue() {
    return this->gen_01_voiceSlot5_128_value;
}

void gen_01_voiceSlot5_128_setvalue(number val) {
    this->gen_01_voiceSlot5_128_value = val;
}

void gen_01_voiceSlot5_128_reset() {
    this->gen_01_voiceSlot5_128_value = 0;
}

void gen_01_voiceSlot5_128_init() {
    this->gen_01_voiceSlot5_128_value = 0;
}

number gen_01_voiceReverse4_127_getvalue() {
    return this->gen_01_voiceReverse4_127_value;
}

void gen_01_voiceReverse4_127_setvalue(number val) {
    this->gen_01_voiceReverse4_127_value = val;
}

void gen_01_voiceReverse4_127_reset() {
    this->gen_01_voiceReverse4_127_value = 0;
}

void gen_01_voiceReverse4_127_init() {
    this->gen_01_voiceReverse4_127_value = 0;
}

number gen_01_voiceLevel4_126_getvalue() {
    return this->gen_01_voiceLevel4_126_value;
}

void gen_01_voiceLevel4_126_setvalue(number val) {
    this->gen_01_voiceLevel4_126_value = val;
}

void gen_01_voiceLevel4_126_reset() {
    this->gen_01_voiceLevel4_126_value = 0;
}

void gen_01_voiceLevel4_126_init() {
    this->gen_01_voiceLevel4_126_value = 0;
}

number gen_01_voiceAttack4_125_getvalue() {
    return this->gen_01_voiceAttack4_125_value;
}

void gen_01_voiceAttack4_125_setvalue(number val) {
    this->gen_01_voiceAttack4_125_value = val;
}

void gen_01_voiceAttack4_125_reset() {
    this->gen_01_voiceAttack4_125_value = 0;
}

void gen_01_voiceAttack4_125_init() {
    this->gen_01_voiceAttack4_125_value = 144;
}

number gen_01_voiceBody4_124_getvalue() {
    return this->gen_01_voiceBody4_124_value;
}

void gen_01_voiceBody4_124_setvalue(number val) {
    this->gen_01_voiceBody4_124_value = val;
}

void gen_01_voiceBody4_124_reset() {
    this->gen_01_voiceBody4_124_value = 0;
}

void gen_01_voiceBody4_124_init() {
    this->gen_01_voiceBody4_124_value = 9600;
}

number gen_01_voicePos4_123_getvalue() {
    return this->gen_01_voicePos4_123_value;
}

void gen_01_voicePos4_123_setvalue(number val) {
    this->gen_01_voicePos4_123_value = val;
}

void gen_01_voicePos4_123_reset() {
    this->gen_01_voicePos4_123_value = 0;
}

void gen_01_voicePos4_123_init() {
    this->gen_01_voicePos4_123_value = 1048576;
}

number gen_01_voiceSlot4_122_getvalue() {
    return this->gen_01_voiceSlot4_122_value;
}

void gen_01_voiceSlot4_122_setvalue(number val) {
    this->gen_01_voiceSlot4_122_value = val;
}

void gen_01_voiceSlot4_122_reset() {
    this->gen_01_voiceSlot4_122_value = 0;
}

void gen_01_voiceSlot4_122_init() {
    this->gen_01_voiceSlot4_122_value = 0;
}

number gen_01_voiceReverse3_121_getvalue() {
    return this->gen_01_voiceReverse3_121_value;
}

void gen_01_voiceReverse3_121_setvalue(number val) {
    this->gen_01_voiceReverse3_121_value = val;
}

void gen_01_voiceReverse3_121_reset() {
    this->gen_01_voiceReverse3_121_value = 0;
}

void gen_01_voiceReverse3_121_init() {
    this->gen_01_voiceReverse3_121_value = 0;
}

number gen_01_voiceLevel3_120_getvalue() {
    return this->gen_01_voiceLevel3_120_value;
}

void gen_01_voiceLevel3_120_setvalue(number val) {
    this->gen_01_voiceLevel3_120_value = val;
}

void gen_01_voiceLevel3_120_reset() {
    this->gen_01_voiceLevel3_120_value = 0;
}

void gen_01_voiceLevel3_120_init() {
    this->gen_01_voiceLevel3_120_value = 0;
}

number gen_01_voiceAttack3_119_getvalue() {
    return this->gen_01_voiceAttack3_119_value;
}

void gen_01_voiceAttack3_119_setvalue(number val) {
    this->gen_01_voiceAttack3_119_value = val;
}

void gen_01_voiceAttack3_119_reset() {
    this->gen_01_voiceAttack3_119_value = 0;
}

void gen_01_voiceAttack3_119_init() {
    this->gen_01_voiceAttack3_119_value = 144;
}

number gen_01_voiceBody3_118_getvalue() {
    return this->gen_01_voiceBody3_118_value;
}

void gen_01_voiceBody3_118_setvalue(number val) {
    this->gen_01_voiceBody3_118_value = val;
}

void gen_01_voiceBody3_118_reset() {
    this->gen_01_voiceBody3_118_value = 0;
}

void gen_01_voiceBody3_118_init() {
    this->gen_01_voiceBody3_118_value = 9600;
}

number gen_01_voicePos3_117_getvalue() {
    return this->gen_01_voicePos3_117_value;
}

void gen_01_voicePos3_117_setvalue(number val) {
    this->gen_01_voicePos3_117_value = val;
}

void gen_01_voicePos3_117_reset() {
    this->gen_01_voicePos3_117_value = 0;
}

void gen_01_voicePos3_117_init() {
    this->gen_01_voicePos3_117_value = 1048576;
}

number gen_01_voiceSlot3_116_getvalue() {
    return this->gen_01_voiceSlot3_116_value;
}

void gen_01_voiceSlot3_116_setvalue(number val) {
    this->gen_01_voiceSlot3_116_value = val;
}

void gen_01_voiceSlot3_116_reset() {
    this->gen_01_voiceSlot3_116_value = 0;
}

void gen_01_voiceSlot3_116_init() {
    this->gen_01_voiceSlot3_116_value = 0;
}

number gen_01_voiceReverse2_115_getvalue() {
    return this->gen_01_voiceReverse2_115_value;
}

void gen_01_voiceReverse2_115_setvalue(number val) {
    this->gen_01_voiceReverse2_115_value = val;
}

void gen_01_voiceReverse2_115_reset() {
    this->gen_01_voiceReverse2_115_value = 0;
}

void gen_01_voiceReverse2_115_init() {
    this->gen_01_voiceReverse2_115_value = 0;
}

number gen_01_voiceLevel2_114_getvalue() {
    return this->gen_01_voiceLevel2_114_value;
}

void gen_01_voiceLevel2_114_setvalue(number val) {
    this->gen_01_voiceLevel2_114_value = val;
}

void gen_01_voiceLevel2_114_reset() {
    this->gen_01_voiceLevel2_114_value = 0;
}

void gen_01_voiceLevel2_114_init() {
    this->gen_01_voiceLevel2_114_value = 0;
}

number gen_01_voiceAttack2_113_getvalue() {
    return this->gen_01_voiceAttack2_113_value;
}

void gen_01_voiceAttack2_113_setvalue(number val) {
    this->gen_01_voiceAttack2_113_value = val;
}

void gen_01_voiceAttack2_113_reset() {
    this->gen_01_voiceAttack2_113_value = 0;
}

void gen_01_voiceAttack2_113_init() {
    this->gen_01_voiceAttack2_113_value = 144;
}

number gen_01_voiceBody2_112_getvalue() {
    return this->gen_01_voiceBody2_112_value;
}

void gen_01_voiceBody2_112_setvalue(number val) {
    this->gen_01_voiceBody2_112_value = val;
}

void gen_01_voiceBody2_112_reset() {
    this->gen_01_voiceBody2_112_value = 0;
}

void gen_01_voiceBody2_112_init() {
    this->gen_01_voiceBody2_112_value = 9600;
}

number gen_01_voicePos2_111_getvalue() {
    return this->gen_01_voicePos2_111_value;
}

void gen_01_voicePos2_111_setvalue(number val) {
    this->gen_01_voicePos2_111_value = val;
}

void gen_01_voicePos2_111_reset() {
    this->gen_01_voicePos2_111_value = 0;
}

void gen_01_voicePos2_111_init() {
    this->gen_01_voicePos2_111_value = 1048576;
}

number gen_01_voiceSlot2_110_getvalue() {
    return this->gen_01_voiceSlot2_110_value;
}

void gen_01_voiceSlot2_110_setvalue(number val) {
    this->gen_01_voiceSlot2_110_value = val;
}

void gen_01_voiceSlot2_110_reset() {
    this->gen_01_voiceSlot2_110_value = 0;
}

void gen_01_voiceSlot2_110_init() {
    this->gen_01_voiceSlot2_110_value = 0;
}

number gen_01_voiceReverse1_109_getvalue() {
    return this->gen_01_voiceReverse1_109_value;
}

void gen_01_voiceReverse1_109_setvalue(number val) {
    this->gen_01_voiceReverse1_109_value = val;
}

void gen_01_voiceReverse1_109_reset() {
    this->gen_01_voiceReverse1_109_value = 0;
}

void gen_01_voiceReverse1_109_init() {
    this->gen_01_voiceReverse1_109_value = 0;
}

number gen_01_voiceLevel1_108_getvalue() {
    return this->gen_01_voiceLevel1_108_value;
}

void gen_01_voiceLevel1_108_setvalue(number val) {
    this->gen_01_voiceLevel1_108_value = val;
}

void gen_01_voiceLevel1_108_reset() {
    this->gen_01_voiceLevel1_108_value = 0;
}

void gen_01_voiceLevel1_108_init() {
    this->gen_01_voiceLevel1_108_value = 0;
}

number gen_01_voiceAttack1_107_getvalue() {
    return this->gen_01_voiceAttack1_107_value;
}

void gen_01_voiceAttack1_107_setvalue(number val) {
    this->gen_01_voiceAttack1_107_value = val;
}

void gen_01_voiceAttack1_107_reset() {
    this->gen_01_voiceAttack1_107_value = 0;
}

void gen_01_voiceAttack1_107_init() {
    this->gen_01_voiceAttack1_107_value = 144;
}

number gen_01_voiceBody1_106_getvalue() {
    return this->gen_01_voiceBody1_106_value;
}

void gen_01_voiceBody1_106_setvalue(number val) {
    this->gen_01_voiceBody1_106_value = val;
}

void gen_01_voiceBody1_106_reset() {
    this->gen_01_voiceBody1_106_value = 0;
}

void gen_01_voiceBody1_106_init() {
    this->gen_01_voiceBody1_106_value = 9600;
}

number gen_01_voicePos1_105_getvalue() {
    return this->gen_01_voicePos1_105_value;
}

void gen_01_voicePos1_105_setvalue(number val) {
    this->gen_01_voicePos1_105_value = val;
}

void gen_01_voicePos1_105_reset() {
    this->gen_01_voicePos1_105_value = 0;
}

void gen_01_voicePos1_105_init() {
    this->gen_01_voicePos1_105_value = 1048576;
}

number gen_01_voiceSlot1_104_getvalue() {
    return this->gen_01_voiceSlot1_104_value;
}

void gen_01_voiceSlot1_104_setvalue(number val) {
    this->gen_01_voiceSlot1_104_value = val;
}

void gen_01_voiceSlot1_104_reset() {
    this->gen_01_voiceSlot1_104_value = 0;
}

void gen_01_voiceSlot1_104_init() {
    this->gen_01_voiceSlot1_104_value = 0;
}

number gen_01_voiceReverse0_103_getvalue() {
    return this->gen_01_voiceReverse0_103_value;
}

void gen_01_voiceReverse0_103_setvalue(number val) {
    this->gen_01_voiceReverse0_103_value = val;
}

void gen_01_voiceReverse0_103_reset() {
    this->gen_01_voiceReverse0_103_value = 0;
}

void gen_01_voiceReverse0_103_init() {
    this->gen_01_voiceReverse0_103_value = 0;
}

number gen_01_voiceLevel0_102_getvalue() {
    return this->gen_01_voiceLevel0_102_value;
}

void gen_01_voiceLevel0_102_setvalue(number val) {
    this->gen_01_voiceLevel0_102_value = val;
}

void gen_01_voiceLevel0_102_reset() {
    this->gen_01_voiceLevel0_102_value = 0;
}

void gen_01_voiceLevel0_102_init() {
    this->gen_01_voiceLevel0_102_value = 0;
}

number gen_01_voiceAttack0_101_getvalue() {
    return this->gen_01_voiceAttack0_101_value;
}

void gen_01_voiceAttack0_101_setvalue(number val) {
    this->gen_01_voiceAttack0_101_value = val;
}

void gen_01_voiceAttack0_101_reset() {
    this->gen_01_voiceAttack0_101_value = 0;
}

void gen_01_voiceAttack0_101_init() {
    this->gen_01_voiceAttack0_101_value = 144;
}

number gen_01_voiceBody0_100_getvalue() {
    return this->gen_01_voiceBody0_100_value;
}

void gen_01_voiceBody0_100_setvalue(number val) {
    this->gen_01_voiceBody0_100_value = val;
}

void gen_01_voiceBody0_100_reset() {
    this->gen_01_voiceBody0_100_value = 0;
}

void gen_01_voiceBody0_100_init() {
    this->gen_01_voiceBody0_100_value = 9600;
}

number gen_01_voicePos0_99_getvalue() {
    return this->gen_01_voicePos0_99_value;
}

void gen_01_voicePos0_99_setvalue(number val) {
    this->gen_01_voicePos0_99_value = val;
}

void gen_01_voicePos0_99_reset() {
    this->gen_01_voicePos0_99_value = 0;
}

void gen_01_voicePos0_99_init() {
    this->gen_01_voicePos0_99_value = 1048576;
}

number gen_01_voiceSlot0_98_getvalue() {
    return this->gen_01_voiceSlot0_98_value;
}

void gen_01_voiceSlot0_98_setvalue(number val) {
    this->gen_01_voiceSlot0_98_value = val;
}

void gen_01_voiceSlot0_98_reset() {
    this->gen_01_voiceSlot0_98_value = 0;
}

void gen_01_voiceSlot0_98_init() {
    this->gen_01_voiceSlot0_98_value = 0;
}

number gen_01_nextVoice_97_getvalue() {
    return this->gen_01_nextVoice_97_value;
}

void gen_01_nextVoice_97_setvalue(number val) {
    this->gen_01_nextVoice_97_value = val;
}

void gen_01_nextVoice_97_reset() {
    this->gen_01_nextVoice_97_value = 0;
}

void gen_01_nextVoice_97_init() {
    this->gen_01_nextVoice_97_value = 0;
}

number gen_01_deferNewest_96_getvalue() {
    return this->gen_01_deferNewest_96_value;
}

void gen_01_deferNewest_96_setvalue(number val) {
    this->gen_01_deferNewest_96_value = val;
}

void gen_01_deferNewest_96_reset() {
    this->gen_01_deferNewest_96_value = 0;
}

void gen_01_deferNewest_96_init() {
    this->gen_01_deferNewest_96_value = 0;
}

number gen_01_rotationRandomState_95_getvalue() {
    return this->gen_01_rotationRandomState_95_value;
}

void gen_01_rotationRandomState_95_setvalue(number val) {
    this->gen_01_rotationRandomState_95_value = val;
}

void gen_01_rotationRandomState_95_reset() {
    this->gen_01_rotationRandomState_95_value = 0;
}

void gen_01_rotationRandomState_95_init() {
    this->gen_01_rotationRandomState_95_value = 0.417;
}

number gen_01_rotationBeatPhase_94_getvalue() {
    return this->gen_01_rotationBeatPhase_94_value;
}

void gen_01_rotationBeatPhase_94_setvalue(number val) {
    this->gen_01_rotationBeatPhase_94_value = val;
}

void gen_01_rotationBeatPhase_94_reset() {
    this->gen_01_rotationBeatPhase_94_value = 0;
}

void gen_01_rotationBeatPhase_94_init() {
    this->gen_01_rotationBeatPhase_94_value = 0;
}

number gen_01_rotationOffset_93_getvalue() {
    return this->gen_01_rotationOffset_93_value;
}

void gen_01_rotationOffset_93_setvalue(number val) {
    this->gen_01_rotationOffset_93_value = val;
}

void gen_01_rotationOffset_93_reset() {
    this->gen_01_rotationOffset_93_value = 0;
}

void gen_01_rotationOffset_93_init() {
    this->gen_01_rotationOffset_93_value = 0;
}

number gen_01_markovActiveBank_92_getvalue() {
    return this->gen_01_markovActiveBank_92_value;
}

void gen_01_markovActiveBank_92_setvalue(number val) {
    this->gen_01_markovActiveBank_92_value = val;
}

void gen_01_markovActiveBank_92_reset() {
    this->gen_01_markovActiveBank_92_value = 0;
}

void gen_01_markovActiveBank_92_init() {
    this->gen_01_markovActiveBank_92_value = 0;
}

number gen_01_previousMarkovCommit_91_getvalue() {
    return this->gen_01_previousMarkovCommit_91_value;
}

void gen_01_previousMarkovCommit_91_setvalue(number val) {
    this->gen_01_previousMarkovCommit_91_value = val;
}

void gen_01_previousMarkovCommit_91_reset() {
    this->gen_01_previousMarkovCommit_91_value = 0;
}

void gen_01_previousMarkovCommit_91_init() {
    this->gen_01_previousMarkovCommit_91_value = 0;
}

number gen_01_previousSelectionMode_90_getvalue() {
    return this->gen_01_previousSelectionMode_90_value;
}

void gen_01_previousSelectionMode_90_setvalue(number val) {
    this->gen_01_previousSelectionMode_90_value = val;
}

void gen_01_previousSelectionMode_90_reset() {
    this->gen_01_previousSelectionMode_90_value = 0;
}

void gen_01_previousSelectionMode_90_init() {
    this->gen_01_previousSelectionMode_90_value = 0;
}

number gen_01_grainRandomState_89_getvalue() {
    return this->gen_01_grainRandomState_89_value;
}

void gen_01_grainRandomState_89_setvalue(number val) {
    this->gen_01_grainRandomState_89_value = val;
}

void gen_01_grainRandomState_89_reset() {
    this->gen_01_grainRandomState_89_value = 0;
}

void gen_01_grainRandomState_89_init() {
    this->gen_01_grainRandomState_89_value = 0.731;
}

number gen_01_grainCursor_88_getvalue() {
    return this->gen_01_grainCursor_88_value;
}

void gen_01_grainCursor_88_setvalue(number val) {
    this->gen_01_grainCursor_88_value = val;
}

void gen_01_grainCursor_88_reset() {
    this->gen_01_grainCursor_88_value = 0;
}

void gen_01_grainCursor_88_init() {
    this->gen_01_grainCursor_88_value = 0;
}

number gen_01_stepIndex_87_getvalue() {
    return this->gen_01_stepIndex_87_value;
}

void gen_01_stepIndex_87_setvalue(number val) {
    this->gen_01_stepIndex_87_value = val;
}

void gen_01_stepIndex_87_reset() {
    this->gen_01_stepIndex_87_value = 0;
}

void gen_01_stepIndex_87_init() {
    this->gen_01_stepIndex_87_value = 0;
}

number gen_01_clockPhase_86_getvalue() {
    return this->gen_01_clockPhase_86_value;
}

void gen_01_clockPhase_86_setvalue(number val) {
    this->gen_01_clockPhase_86_value = val;
}

void gen_01_clockPhase_86_reset() {
    this->gen_01_clockPhase_86_value = 0;
}

void gen_01_clockPhase_86_init() {
    this->gen_01_clockPhase_86_value = 0;
}

number gen_01_poolCount_85_getvalue() {
    return this->gen_01_poolCount_85_value;
}

void gen_01_poolCount_85_setvalue(number val) {
    this->gen_01_poolCount_85_value = val;
}

void gen_01_poolCount_85_reset() {
    this->gen_01_poolCount_85_value = 0;
}

void gen_01_poolCount_85_init() {
    this->gen_01_poolCount_85_value = 0;
}

number gen_01_captureSlot_84_getvalue() {
    return this->gen_01_captureSlot_84_value;
}

void gen_01_captureSlot_84_setvalue(number val) {
    this->gen_01_captureSlot_84_value = val;
}

void gen_01_captureSlot_84_reset() {
    this->gen_01_captureSlot_84_value = 0;
}

void gen_01_captureSlot_84_init() {
    this->gen_01_captureSlot_84_value = 0;
}

number gen_01_rearmCounter_83_getvalue() {
    return this->gen_01_rearmCounter_83_value;
}

void gen_01_rearmCounter_83_setvalue(number val) {
    this->gen_01_rearmCounter_83_value = val;
}

void gen_01_rearmCounter_83_reset() {
    this->gen_01_rearmCounter_83_value = 0;
}

void gen_01_rearmCounter_83_init() {
    this->gen_01_rearmCounter_83_value = 0;
}

number gen_01_onsetArmed_82_getvalue() {
    return this->gen_01_onsetArmed_82_value;
}

void gen_01_onsetArmed_82_setvalue(number val) {
    this->gen_01_onsetArmed_82_value = val;
}

void gen_01_onsetArmed_82_reset() {
    this->gen_01_onsetArmed_82_value = 0;
}

void gen_01_onsetArmed_82_init() {
    this->gen_01_onsetArmed_82_value = 1;
}

number gen_01_cooldown_81_getvalue() {
    return this->gen_01_cooldown_81_value;
}

void gen_01_cooldown_81_setvalue(number val) {
    this->gen_01_cooldown_81_value = val;
}

void gen_01_cooldown_81_reset() {
    this->gen_01_cooldown_81_value = 0;
}

void gen_01_cooldown_81_init() {
    this->gen_01_cooldown_81_value = 0;
}

number gen_01_adaptiveThreshold_80_getvalue() {
    return this->gen_01_adaptiveThreshold_80_value;
}

void gen_01_adaptiveThreshold_80_setvalue(number val) {
    this->gen_01_adaptiveThreshold_80_value = val;
}

void gen_01_adaptiveThreshold_80_reset() {
    this->gen_01_adaptiveThreshold_80_value = 0;
}

void gen_01_adaptiveThreshold_80_init() {
    this->gen_01_adaptiveThreshold_80_value = 0.032;
}

number gen_01_activityEnv_79_getvalue() {
    return this->gen_01_activityEnv_79_value;
}

void gen_01_activityEnv_79_setvalue(number val) {
    this->gen_01_activityEnv_79_value = val;
}

void gen_01_activityEnv_79_reset() {
    this->gen_01_activityEnv_79_value = 0;
}

void gen_01_activityEnv_79_init() {
    this->gen_01_activityEnv_79_value = 0;
}

number gen_01_levelEnv_78_getvalue() {
    return this->gen_01_levelEnv_78_value;
}

void gen_01_levelEnv_78_setvalue(number val) {
    this->gen_01_levelEnv_78_value = val;
}

void gen_01_levelEnv_78_reset() {
    this->gen_01_levelEnv_78_value = 0;
}

void gen_01_levelEnv_78_init() {
    this->gen_01_levelEnv_78_value = 0;
}

number gen_01_slowEnv_77_getvalue() {
    return this->gen_01_slowEnv_77_value;
}

void gen_01_slowEnv_77_setvalue(number val) {
    this->gen_01_slowEnv_77_value = val;
}

void gen_01_slowEnv_77_reset() {
    this->gen_01_slowEnv_77_value = 0;
}

void gen_01_slowEnv_77_init() {
    this->gen_01_slowEnv_77_value = 0;
}

number gen_01_fastEnv_76_getvalue() {
    return this->gen_01_fastEnv_76_value;
}

void gen_01_fastEnv_76_setvalue(number val) {
    this->gen_01_fastEnv_76_value = val;
}

void gen_01_fastEnv_76_reset() {
    this->gen_01_fastEnv_76_value = 0;
}

void gen_01_fastEnv_76_init() {
    this->gen_01_fastEnv_76_value = 0;
}

void gen_01_feedbackR_75_step() {
    this->gen_01_feedbackR_75_reader++;

    if (this->gen_01_feedbackR_75_reader >= (Int)(this->gen_01_feedbackR_75_buffer->getSize()))
        this->gen_01_feedbackR_75_reader = 0;
}

number gen_01_feedbackR_75_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (Int)(this->gen_01_feedbackR_75_buffer->getSize()) + this->gen_01_feedbackR_75_reader - ((size > this->gen_01_feedbackR_75__maxdelay ? this->gen_01_feedbackR_75__maxdelay : (size < (this->gen_01_feedbackR_75_reader != this->gen_01_feedbackR_75_writer) ? this->gen_01_feedbackR_75_reader != this->gen_01_feedbackR_75_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_feedbackR_75_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_feedbackR_75_wrap))
        ), this->gen_01_feedbackR_75_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_feedbackR_75_wrap))
        ));
    }

    number r = (Int)(this->gen_01_feedbackR_75_buffer->getSize()) + this->gen_01_feedbackR_75_reader - ((size > this->gen_01_feedbackR_75__maxdelay ? this->gen_01_feedbackR_75__maxdelay : (size < (this->gen_01_feedbackR_75_reader != this->gen_01_feedbackR_75_writer) ? this->gen_01_feedbackR_75_reader != this->gen_01_feedbackR_75_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_feedbackR_75_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_feedbackR_75_wrap))
    );
}

void gen_01_feedbackR_75_write(number v) {
    this->gen_01_feedbackR_75_writer = this->gen_01_feedbackR_75_reader;
    this->gen_01_feedbackR_75_buffer[(Index)this->gen_01_feedbackR_75_writer] = v;
}

number gen_01_feedbackR_75_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->gen_01_feedbackR_75__maxdelay : size);
    number val = this->gen_01_feedbackR_75_read(effectiveSize, 0);
    this->gen_01_feedbackR_75_write(v);
    this->gen_01_feedbackR_75_step();
    return val;
}

array<Index, 2> gen_01_feedbackR_75_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_feedbackR_75_evaluateSizeExpr(this->sr, this->vs);
        this->gen_01_feedbackR_75_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_feedbackR_75_init() {
    auto result = this->gen_01_feedbackR_75_calcSizeInSamples();
    this->gen_01_feedbackR_75__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_feedbackR_75_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_feedbackR_75_wrap = requestedSizeInSamples - 1;
}

void gen_01_feedbackR_75_clear() {
    this->gen_01_feedbackR_75_buffer->setZero();
}

void gen_01_feedbackR_75_reset() {
    auto result = this->gen_01_feedbackR_75_calcSizeInSamples();
    this->gen_01_feedbackR_75__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_feedbackR_75_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_feedbackR_75_buffer);
    this->gen_01_feedbackR_75_wrap = this->gen_01_feedbackR_75_buffer->getSize() - 1;
    this->gen_01_feedbackR_75_clear();

    if (this->gen_01_feedbackR_75_reader >= this->gen_01_feedbackR_75__maxdelay || this->gen_01_feedbackR_75_writer >= this->gen_01_feedbackR_75__maxdelay) {
        this->gen_01_feedbackR_75_reader = 0;
        this->gen_01_feedbackR_75_writer = 0;
    }
}

void gen_01_feedbackR_75_dspsetup() {
    this->gen_01_feedbackR_75_reset();
}

number gen_01_feedbackR_75_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 4194304;
}

number gen_01_feedbackR_75_size() {
    return this->gen_01_feedbackR_75__maxdelay;
}

void gen_01_feedbackL_74_step() {
    this->gen_01_feedbackL_74_reader++;

    if (this->gen_01_feedbackL_74_reader >= (Int)(this->gen_01_feedbackL_74_buffer->getSize()))
        this->gen_01_feedbackL_74_reader = 0;
}

number gen_01_feedbackL_74_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (Int)(this->gen_01_feedbackL_74_buffer->getSize()) + this->gen_01_feedbackL_74_reader - ((size > this->gen_01_feedbackL_74__maxdelay ? this->gen_01_feedbackL_74__maxdelay : (size < (this->gen_01_feedbackL_74_reader != this->gen_01_feedbackL_74_writer) ? this->gen_01_feedbackL_74_reader != this->gen_01_feedbackL_74_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_feedbackL_74_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_feedbackL_74_wrap))
        ), this->gen_01_feedbackL_74_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_feedbackL_74_wrap))
        ));
    }

    number r = (Int)(this->gen_01_feedbackL_74_buffer->getSize()) + this->gen_01_feedbackL_74_reader - ((size > this->gen_01_feedbackL_74__maxdelay ? this->gen_01_feedbackL_74__maxdelay : (size < (this->gen_01_feedbackL_74_reader != this->gen_01_feedbackL_74_writer) ? this->gen_01_feedbackL_74_reader != this->gen_01_feedbackL_74_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_feedbackL_74_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_feedbackL_74_wrap))
    );
}

void gen_01_feedbackL_74_write(number v) {
    this->gen_01_feedbackL_74_writer = this->gen_01_feedbackL_74_reader;
    this->gen_01_feedbackL_74_buffer[(Index)this->gen_01_feedbackL_74_writer] = v;
}

number gen_01_feedbackL_74_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->gen_01_feedbackL_74__maxdelay : size);
    number val = this->gen_01_feedbackL_74_read(effectiveSize, 0);
    this->gen_01_feedbackL_74_write(v);
    this->gen_01_feedbackL_74_step();
    return val;
}

array<Index, 2> gen_01_feedbackL_74_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_feedbackL_74_evaluateSizeExpr(this->sr, this->vs);
        this->gen_01_feedbackL_74_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_feedbackL_74_init() {
    auto result = this->gen_01_feedbackL_74_calcSizeInSamples();
    this->gen_01_feedbackL_74__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_feedbackL_74_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_feedbackL_74_wrap = requestedSizeInSamples - 1;
}

void gen_01_feedbackL_74_clear() {
    this->gen_01_feedbackL_74_buffer->setZero();
}

void gen_01_feedbackL_74_reset() {
    auto result = this->gen_01_feedbackL_74_calcSizeInSamples();
    this->gen_01_feedbackL_74__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_feedbackL_74_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_feedbackL_74_buffer);
    this->gen_01_feedbackL_74_wrap = this->gen_01_feedbackL_74_buffer->getSize() - 1;
    this->gen_01_feedbackL_74_clear();

    if (this->gen_01_feedbackL_74_reader >= this->gen_01_feedbackL_74__maxdelay || this->gen_01_feedbackL_74_writer >= this->gen_01_feedbackL_74__maxdelay) {
        this->gen_01_feedbackL_74_reader = 0;
        this->gen_01_feedbackL_74_writer = 0;
    }
}

void gen_01_feedbackL_74_dspsetup() {
    this->gen_01_feedbackL_74_reset();
}

number gen_01_feedbackL_74_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 4194304;
}

number gen_01_feedbackL_74_size() {
    return this->gen_01_feedbackL_74__maxdelay;
}

void gen_01_triggerDelay_73_step() {
    this->gen_01_triggerDelay_73_reader++;

    if (this->gen_01_triggerDelay_73_reader >= (Int)(this->gen_01_triggerDelay_73_buffer->getSize()))
        this->gen_01_triggerDelay_73_reader = 0;
}

number gen_01_triggerDelay_73_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (Int)(this->gen_01_triggerDelay_73_buffer->getSize()) + this->gen_01_triggerDelay_73_reader - ((size > this->gen_01_triggerDelay_73__maxdelay ? this->gen_01_triggerDelay_73__maxdelay : (size < (this->gen_01_triggerDelay_73_reader != this->gen_01_triggerDelay_73_writer) ? this->gen_01_triggerDelay_73_reader != this->gen_01_triggerDelay_73_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_triggerDelay_73_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_triggerDelay_73_wrap))
        ), this->gen_01_triggerDelay_73_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_triggerDelay_73_wrap))
        ));
    }

    number r = (Int)(this->gen_01_triggerDelay_73_buffer->getSize()) + this->gen_01_triggerDelay_73_reader - ((size > this->gen_01_triggerDelay_73__maxdelay ? this->gen_01_triggerDelay_73__maxdelay : (size < (this->gen_01_triggerDelay_73_reader != this->gen_01_triggerDelay_73_writer) ? this->gen_01_triggerDelay_73_reader != this->gen_01_triggerDelay_73_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_triggerDelay_73_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_triggerDelay_73_wrap))
    );
}

void gen_01_triggerDelay_73_write(number v) {
    this->gen_01_triggerDelay_73_writer = this->gen_01_triggerDelay_73_reader;
    this->gen_01_triggerDelay_73_buffer[(Index)this->gen_01_triggerDelay_73_writer] = v;
}

number gen_01_triggerDelay_73_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->gen_01_triggerDelay_73__maxdelay : size);
    number val = this->gen_01_triggerDelay_73_read(effectiveSize, 0);
    this->gen_01_triggerDelay_73_write(v);
    this->gen_01_triggerDelay_73_step();
    return val;
}

array<Index, 2> gen_01_triggerDelay_73_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_triggerDelay_73_evaluateSizeExpr(this->sr, this->vs);
        this->gen_01_triggerDelay_73_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_triggerDelay_73_init() {
    auto result = this->gen_01_triggerDelay_73_calcSizeInSamples();
    this->gen_01_triggerDelay_73__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_triggerDelay_73_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_triggerDelay_73_wrap = requestedSizeInSamples - 1;
}

void gen_01_triggerDelay_73_clear() {
    this->gen_01_triggerDelay_73_buffer->setZero();
}

void gen_01_triggerDelay_73_reset() {
    auto result = this->gen_01_triggerDelay_73_calcSizeInSamples();
    this->gen_01_triggerDelay_73__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_triggerDelay_73_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_triggerDelay_73_buffer);
    this->gen_01_triggerDelay_73_wrap = this->gen_01_triggerDelay_73_buffer->getSize() - 1;
    this->gen_01_triggerDelay_73_clear();

    if (this->gen_01_triggerDelay_73_reader >= this->gen_01_triggerDelay_73__maxdelay || this->gen_01_triggerDelay_73_writer >= this->gen_01_triggerDelay_73__maxdelay) {
        this->gen_01_triggerDelay_73_reader = 0;
        this->gen_01_triggerDelay_73_writer = 0;
    }
}

void gen_01_triggerDelay_73_dspsetup() {
    this->gen_01_triggerDelay_73_reset();
}

number gen_01_triggerDelay_73_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 524288;
}

number gen_01_triggerDelay_73_size() {
    return this->gen_01_triggerDelay_73__maxdelay;
}

void gen_01_preR_72_step() {
    this->gen_01_preR_72_reader++;

    if (this->gen_01_preR_72_reader >= (Int)(this->gen_01_preR_72_buffer->getSize()))
        this->gen_01_preR_72_reader = 0;
}

number gen_01_preR_72_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (Int)(this->gen_01_preR_72_buffer->getSize()) + this->gen_01_preR_72_reader - ((size > this->gen_01_preR_72__maxdelay ? this->gen_01_preR_72__maxdelay : (size < (this->gen_01_preR_72_reader != this->gen_01_preR_72_writer) ? this->gen_01_preR_72_reader != this->gen_01_preR_72_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_preR_72_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_preR_72_wrap))
        ), this->gen_01_preR_72_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_preR_72_wrap))
        ));
    }

    number r = (Int)(this->gen_01_preR_72_buffer->getSize()) + this->gen_01_preR_72_reader - ((size > this->gen_01_preR_72__maxdelay ? this->gen_01_preR_72__maxdelay : (size < (this->gen_01_preR_72_reader != this->gen_01_preR_72_writer) ? this->gen_01_preR_72_reader != this->gen_01_preR_72_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_preR_72_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_preR_72_wrap))
    );
}

void gen_01_preR_72_write(number v) {
    this->gen_01_preR_72_writer = this->gen_01_preR_72_reader;
    this->gen_01_preR_72_buffer[(Index)this->gen_01_preR_72_writer] = v;
}

number gen_01_preR_72_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->gen_01_preR_72__maxdelay : size);
    number val = this->gen_01_preR_72_read(effectiveSize, 0);
    this->gen_01_preR_72_write(v);
    this->gen_01_preR_72_step();
    return val;
}

array<Index, 2> gen_01_preR_72_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_preR_72_evaluateSizeExpr(this->sr, this->vs);
        this->gen_01_preR_72_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_preR_72_init() {
    auto result = this->gen_01_preR_72_calcSizeInSamples();
    this->gen_01_preR_72__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_preR_72_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_preR_72_wrap = requestedSizeInSamples - 1;
}

void gen_01_preR_72_clear() {
    this->gen_01_preR_72_buffer->setZero();
}

void gen_01_preR_72_reset() {
    auto result = this->gen_01_preR_72_calcSizeInSamples();
    this->gen_01_preR_72__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_preR_72_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_preR_72_buffer);
    this->gen_01_preR_72_wrap = this->gen_01_preR_72_buffer->getSize() - 1;
    this->gen_01_preR_72_clear();

    if (this->gen_01_preR_72_reader >= this->gen_01_preR_72__maxdelay || this->gen_01_preR_72_writer >= this->gen_01_preR_72__maxdelay) {
        this->gen_01_preR_72_reader = 0;
        this->gen_01_preR_72_writer = 0;
    }
}

void gen_01_preR_72_dspsetup() {
    this->gen_01_preR_72_reset();
}

number gen_01_preR_72_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 8192;
}

number gen_01_preR_72_size() {
    return this->gen_01_preR_72__maxdelay;
}

void gen_01_preL_71_step() {
    this->gen_01_preL_71_reader++;

    if (this->gen_01_preL_71_reader >= (Int)(this->gen_01_preL_71_buffer->getSize()))
        this->gen_01_preL_71_reader = 0;
}

number gen_01_preL_71_read(number size, Int interp) {
    RNBO_UNUSED(interp);

    {
        number r = (Int)(this->gen_01_preL_71_buffer->getSize()) + this->gen_01_preL_71_reader - ((size > this->gen_01_preL_71__maxdelay ? this->gen_01_preL_71__maxdelay : (size < (this->gen_01_preL_71_reader != this->gen_01_preL_71_writer) ? this->gen_01_preL_71_reader != this->gen_01_preL_71_writer : size)));
        Int index1 = (Int)(rnbo_floor(r));
        number frac = r - index1;
        Int index2 = (Int)(index1 + 1);

        return this->linearinterp(frac, this->gen_01_preL_71_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_preL_71_wrap))
        ), this->gen_01_preL_71_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->gen_01_preL_71_wrap))
        ));
    }

    number r = (Int)(this->gen_01_preL_71_buffer->getSize()) + this->gen_01_preL_71_reader - ((size > this->gen_01_preL_71__maxdelay ? this->gen_01_preL_71__maxdelay : (size < (this->gen_01_preL_71_reader != this->gen_01_preL_71_writer) ? this->gen_01_preL_71_reader != this->gen_01_preL_71_writer : size)));
    Int index1 = (Int)(rnbo_floor(r));

    return this->gen_01_preL_71_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->gen_01_preL_71_wrap))
    );
}

void gen_01_preL_71_write(number v) {
    this->gen_01_preL_71_writer = this->gen_01_preL_71_reader;
    this->gen_01_preL_71_buffer[(Index)this->gen_01_preL_71_writer] = v;
}

number gen_01_preL_71_next(number v, Int size) {
    number effectiveSize = (size == -1 ? this->gen_01_preL_71__maxdelay : size);
    number val = this->gen_01_preL_71_read(effectiveSize, 0);
    this->gen_01_preL_71_write(v);
    this->gen_01_preL_71_step();
    return val;
}

array<Index, 2> gen_01_preL_71_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->gen_01_preL_71_evaluateSizeExpr(this->sr, this->vs);
        this->gen_01_preL_71_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void gen_01_preL_71_init() {
    auto result = this->gen_01_preL_71_calcSizeInSamples();
    this->gen_01_preL_71__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->gen_01_preL_71_buffer->requestSize(requestedSizeInSamples, 1);
    this->gen_01_preL_71_wrap = requestedSizeInSamples - 1;
}

void gen_01_preL_71_clear() {
    this->gen_01_preL_71_buffer->setZero();
}

void gen_01_preL_71_reset() {
    auto result = this->gen_01_preL_71_calcSizeInSamples();
    this->gen_01_preL_71__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->gen_01_preL_71_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->gen_01_preL_71_buffer);
    this->gen_01_preL_71_wrap = this->gen_01_preL_71_buffer->getSize() - 1;
    this->gen_01_preL_71_clear();

    if (this->gen_01_preL_71_reader >= this->gen_01_preL_71__maxdelay || this->gen_01_preL_71_writer >= this->gen_01_preL_71__maxdelay) {
        this->gen_01_preL_71_reader = 0;
        this->gen_01_preL_71_writer = 0;
    }
}

void gen_01_preL_71_dspsetup() {
    this->gen_01_preL_71_reset();
}

number gen_01_preL_71_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    return 8192;
}

number gen_01_preL_71_size() {
    return this->gen_01_preL_71__maxdelay;
}

void gen_01_dspsetup(bool force) {
    if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_01_setupDone = true;
    this->gen_01_feedbackR_75_dspsetup();
    this->gen_01_feedbackL_74_dspsetup();
    this->gen_01_triggerDelay_73_dspsetup();
    this->gen_01_preR_72_dspsetup();
    this->gen_01_preL_71_dspsetup();
}

void transport_01_onTempoChanged(number state) {
    this->transport_01_outtempo_set(state);
}

void transport_01_onTransportChanged(number state) {
    this->transport_01_state_set(state);
}

void transport_01_onTimeSignatureChanged(number numerator, number denominator) {
    this->transport_01_outtimesig_set(listbase<number, 2>{numerator, denominator});
}

void gen_01_param_ScatterloomDSP_sensitivity_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_sensitivity_value;
}

void gen_01_param_ScatterloomDSP_sensitivity_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_sensitivity_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_autoSensitivity_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_autoSensitivity_value;
}

void gen_01_param_ScatterloomDSP_autoSensitivity_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_autoSensitivity_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_captureOn_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_captureOn_value;
}

void gen_01_param_ScatterloomDSP_captureOn_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_captureOn_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grain_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grain_value;
}

void gen_01_param_ScatterloomDSP_grain_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grain_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_attack_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_attack_value;
}

void gen_01_param_ScatterloomDSP_attack_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_attack_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainCount_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainCount_value;
}

void gen_01_param_ScatterloomDSP_grainCount_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainCount_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_steps_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_steps_value;
}

void gen_01_param_ScatterloomDSP_steps_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_steps_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_pulses_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_pulses_value;
}

void gen_01_param_ScatterloomDSP_pulses_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_pulses_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_rotation_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_rotation_value;
}

void gen_01_param_ScatterloomDSP_rotation_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_rotation_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_feedback_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_feedback_value;
}

void gen_01_param_ScatterloomDSP_feedback_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_feedback_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_mixAmount_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_mixAmount_value;
}

void gen_01_param_ScatterloomDSP_mixAmount_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_mixAmount_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainFeedback_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainFeedback_value;
}

void gen_01_param_ScatterloomDSP_grainFeedback_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainFeedback_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_reverseProbability_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_reverseProbability_value;
}

void gen_01_param_ScatterloomDSP_reverseProbability_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_reverseProbability_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_clearPool_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_clearPool_value;
}

void gen_01_param_ScatterloomDSP_clearPool_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_clearPool_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_division_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_division_value;
}

void gen_01_param_ScatterloomDSP_division_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_division_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_rotationInterval_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_rotationInterval_value;
}

void gen_01_param_ScatterloomDSP_rotationInterval_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_rotationInterval_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan0_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan0_value;
}

void gen_01_param_ScatterloomDSP_grainPan0_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan0_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan1_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan1_value;
}

void gen_01_param_ScatterloomDSP_grainPan1_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan1_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan2_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan2_value;
}

void gen_01_param_ScatterloomDSP_grainPan2_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan2_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan3_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan3_value;
}

void gen_01_param_ScatterloomDSP_grainPan3_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan3_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan4_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan4_value;
}

void gen_01_param_ScatterloomDSP_grainPan4_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan4_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan5_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan5_value;
}

void gen_01_param_ScatterloomDSP_grainPan5_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan5_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan6_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan6_value;
}

void gen_01_param_ScatterloomDSP_grainPan6_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan6_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan7_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan7_value;
}

void gen_01_param_ScatterloomDSP_grainPan7_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan7_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainPan8_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainPan8_value;
}

void gen_01_param_ScatterloomDSP_grainPan8_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainPan8_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_grainSelectionMode_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_grainSelectionMode_value;
}

void gen_01_param_ScatterloomDSP_grainSelectionMode_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_grainSelectionMode_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_loopDivision_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_loopDivision_value;
}

void gen_01_param_ScatterloomDSP_loopDivision_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_loopDivision_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_timingOffset_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_timingOffset_value;
}

void gen_01_param_ScatterloomDSP_timingOffset_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_timingOffset_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_removeGrain_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_removeGrain_value;
}

void gen_01_param_ScatterloomDSP_removeGrain_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_removeGrain_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_auditionGrain_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_auditionGrain_value;
}

void gen_01_param_ScatterloomDSP_auditionGrain_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_auditionGrain_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_reorderFrom_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_reorderFrom_value;
}

void gen_01_param_ScatterloomDSP_reorderFrom_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_reorderFrom_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_reorderTo_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_reorderTo_value;
}

void gen_01_param_ScatterloomDSP_reorderTo_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_reorderTo_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_reorderCommit_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_reorderCommit_value;
}

void gen_01_param_ScatterloomDSP_reorderCommit_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_reorderCommit_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight0_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight0_value;
}

void gen_01_param_ScatterloomDSP_markovWeight0_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight0_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight1_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight1_value;
}

void gen_01_param_ScatterloomDSP_markovWeight1_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight1_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight2_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight2_value;
}

void gen_01_param_ScatterloomDSP_markovWeight2_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight2_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight3_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight3_value;
}

void gen_01_param_ScatterloomDSP_markovWeight3_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight3_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight4_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight4_value;
}

void gen_01_param_ScatterloomDSP_markovWeight4_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight4_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight5_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight5_value;
}

void gen_01_param_ScatterloomDSP_markovWeight5_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight5_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight6_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight6_value;
}

void gen_01_param_ScatterloomDSP_markovWeight6_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight6_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight7_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight7_value;
}

void gen_01_param_ScatterloomDSP_markovWeight7_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight7_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovWeight8_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovWeight8_value;
}

void gen_01_param_ScatterloomDSP_markovWeight8_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovWeight8_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovEditRow_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovEditRow_value;
}

void gen_01_param_ScatterloomDSP_markovEditRow_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovEditRow_value_set(preset["value"]);
}

void gen_01_param_ScatterloomDSP_markovCommit_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gen_01_param_ScatterloomDSP_markovCommit_value;
}

void gen_01_param_ScatterloomDSP_markovCommit_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gen_01_param_ScatterloomDSP_markovCommit_value_set(preset["value"]);
}

number globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    number diffInBeats = diff * this->globaltransport_getTempo(time) * 0.008 / (number)480;
    return beatTimeBase + diffInBeats;
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample((SampleIndex)(offset)) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        SampleIndex offset = (SampleIndex)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_state, this->vs, state, (Index)(offset));
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        number currentBeatTime = this->globaltransport_getBeatTime(time);

        if (rnbo_abs(beattime - currentBeatTime) > 0.001) {
            beatTimeHasChanged = true;
            this->globaltransport_beatTimeChanges->push(beattime);
            this->globaltransport_beatTimeChanges->push(time);
        } else {
            this->globaltransport_beatTimeChanges->push(currentBeatTime);
            this->globaltransport_beatTimeChanges->push(time);
        }

        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = (MillisecondTime)(this->sampstoms(sampleOffset));
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

void globaltransport_setBBUBase(
    MillisecondTime time,
    number numerator,
    number denominator,
    number bars,
    number beats,
    number units
) {
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    bars--;
    beats--;
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;

    while (units > beatLengthInUnits) {
        units -= beatLengthInUnits;
        beats++;
    }

    number targetBeatTime = bars * numerator + beats + units / beatLengthInUnits;
    this->globaltransport_bbuBase = targetBeatTime - beatsIncCurrenttDenom;
}

array<number, 3> globaltransport_getBBU(MillisecondTime time) {
    array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);
    number numerator = currentSig[0];
    number denominator = currentSig[1];
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;
    number targetBeatTime = beatsIncCurrenttDenom + this->globaltransport_bbuBase;
    number currentBars = 0;
    number currentBeats = 0;
    number currentUnits = 0;

    if (targetBeatTime >= 0) {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;
        currentBeats = trunc(targetBeatTime);
        targetBeatTime -= currentBeats;
        currentUnits = targetBeatTime * beatLengthInUnits;
    } else {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;

        if (targetBeatTime != 0) {
            currentBars -= 1;
            currentBeats = trunc(targetBeatTime);
            targetBeatTime -= currentBeats;
            currentBeats = numerator + currentBeats;
            currentUnits = targetBeatTime * beatLengthInUnits;

            if (currentUnits != 0) {
                currentUnits = beatLengthInUnits + currentUnits;
                currentBeats -= 1;
            }
        }
    }

    return {currentBars + 1, currentBeats + 1, currentUnits};
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (Int)(numerator), (Int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            array<number, 3> bbu = this->globaltransport_getBBU(time);
            this->globaltransport_setBBUBase(time, numerator, denominator, bbu[0], bbu[1], bbu[2]);
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

array<number, 3> globaltransport_getBBUAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBBU(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setBBU(MillisecondTime time, number bars, number beats, number units, bool notify) {
    RNBO_UNUSED(notify);
    array<number, 2> sig = this->globaltransport_getTimeSignature(time);
    number numerator = sig[0];
    number denominator = sig[1];
    this->globaltransport_setBBUBase(time, numerator, denominator, bars, beats, units);
    return true;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (Int)(this->globaltransport_timeSignatureChanges[0]),
                (Int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
    RNBO_UNUSED(inProcess);
    RNBO_UNUSED(engine);
    this->_currentTime = time;
    auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));

    if (offset >= (SampleIndex)(this->vs))
        offset = (SampleIndex)(this->vs) - 1;

    if (offset < 0)
        offset = 0;

    this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
}

void assign_defaults()
{
    gen_01_in1 = 0;
    gen_01_in2 = 0;
    gen_01_in3 = 0;
    gen_01_in4 = 0;
    gen_01_in5 = 0;
    gen_01_sensitivity = 0.35;
    gen_01_autoSensitivity = 1;
    gen_01_captureOn = 1;
    gen_01_grain = 0.33;
    gen_01_attack = 0;
    gen_01_grainCount = 5;
    gen_01_steps = 16;
    gen_01_pulses = 5;
    gen_01_rotation = 0;
    gen_01_feedback = 0.35;
    gen_01_mixAmount = 0.5;
    gen_01_grainFeedback = 1;
    gen_01_reverseProbability = 0;
    gen_01_clearPool = 0;
    gen_01_division = 10;
    gen_01_rotationInterval = 0;
    gen_01_grainPan0 = -0.5;
    gen_01_grainPan1 = 0.5;
    gen_01_grainPan2 = -0.25;
    gen_01_grainPan3 = 0.25;
    gen_01_grainPan4 = 0;
    gen_01_grainPan5 = -0.375;
    gen_01_grainPan6 = 0.375;
    gen_01_grainPan7 = -0.125;
    gen_01_grainPan8 = 0.125;
    gen_01_grainSelectionMode = 0;
    gen_01_loopDivision = 4;
    gen_01_timingOffset = 0;
    gen_01_removeGrain = 0;
    gen_01_auditionGrain = 0;
    gen_01_reorderFrom = 0;
    gen_01_reorderTo = 0;
    gen_01_reorderCommit = 0;
    gen_01_markovWeight0 = 0.111111;
    gen_01_markovWeight1 = 0.111111;
    gen_01_markovWeight2 = 0.111111;
    gen_01_markovWeight3 = 0.111111;
    gen_01_markovWeight4 = 0.111111;
    gen_01_markovWeight5 = 0.111111;
    gen_01_markovWeight6 = 0.111111;
    gen_01_markovWeight7 = 0.111111;
    gen_01_markovWeight8 = 0.111111;
    gen_01_markovEditRow = 0;
    gen_01_markovCommit = 0;
    transport_01_input_number = 0;
    transport_01_position = 0;
    transport_01_tempo = 120;
    transport_01_ticks = 0;
    beatstosamps_tilde_01_beattime = 1;
    gen_01_param_ScatterloomDSP_sensitivity_value = 0.35;
    gen_01_param_ScatterloomDSP_autoSensitivity_value = 1;
    gen_01_param_ScatterloomDSP_captureOn_value = 1;
    gen_01_param_ScatterloomDSP_grain_value = 0.33;
    gen_01_param_ScatterloomDSP_attack_value = 0;
    gen_01_param_ScatterloomDSP_grainCount_value = 5;
    gen_01_param_ScatterloomDSP_steps_value = 16;
    gen_01_param_ScatterloomDSP_pulses_value = 5;
    gen_01_param_ScatterloomDSP_rotation_value = 0;
    gen_01_param_ScatterloomDSP_feedback_value = 0.35;
    gen_01_param_ScatterloomDSP_mixAmount_value = 0.5;
    gen_01_param_ScatterloomDSP_grainFeedback_value = 1;
    gen_01_param_ScatterloomDSP_reverseProbability_value = 0;
    gen_01_param_ScatterloomDSP_clearPool_value = 0;
    gen_01_param_ScatterloomDSP_division_value = 10;
    gen_01_param_ScatterloomDSP_rotationInterval_value = 0;
    gen_01_param_ScatterloomDSP_grainPan0_value = -0.5;
    gen_01_param_ScatterloomDSP_grainPan1_value = 0.5;
    gen_01_param_ScatterloomDSP_grainPan2_value = -0.25;
    gen_01_param_ScatterloomDSP_grainPan3_value = 0.25;
    gen_01_param_ScatterloomDSP_grainPan4_value = 0;
    gen_01_param_ScatterloomDSP_grainPan5_value = -0.375;
    gen_01_param_ScatterloomDSP_grainPan6_value = 0.375;
    gen_01_param_ScatterloomDSP_grainPan7_value = -0.125;
    gen_01_param_ScatterloomDSP_grainPan8_value = 0.125;
    gen_01_param_ScatterloomDSP_grainSelectionMode_value = 0;
    gen_01_param_ScatterloomDSP_loopDivision_value = 4;
    gen_01_param_ScatterloomDSP_timingOffset_value = 0;
    gen_01_param_ScatterloomDSP_removeGrain_value = 0;
    gen_01_param_ScatterloomDSP_auditionGrain_value = 0;
    gen_01_param_ScatterloomDSP_reorderFrom_value = 0;
    gen_01_param_ScatterloomDSP_reorderTo_value = 0;
    gen_01_param_ScatterloomDSP_reorderCommit_value = 0;
    gen_01_param_ScatterloomDSP_markovWeight0_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight1_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight2_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight3_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight4_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight5_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight6_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight7_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovWeight8_value = 0.111111;
    gen_01_param_ScatterloomDSP_markovEditRow_value = 0;
    gen_01_param_ScatterloomDSP_markovCommit_value = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    gen_01_slide_198_prev = 0;
    gen_01_slide_200_prev = 0;
    gen_01_slide_202_prev = 0;
    gen_01_slide_204_prev = 0;
    gen_01_slide_206_prev = 0;
    gen_01_slide_208_prev = 0;
    gen_01_slide_210_prev = 0;
    gen_01_slide_212_prev = 0;
    gen_01_feedbackAge_197_value = 0;
    gen_01_loopDelayFade_196_value = 0;
    gen_01_previousLoopDelaySamples_195_value = 0;
    gen_01_loopDelaySamples_194_value = 0;
    gen_01_auditionStart_193_value = 0;
    gen_01_auditionLevel_192_value = 0;
    gen_01_auditionAttack_191_value = 0;
    gen_01_auditionBody_190_value = 0;
    gen_01_auditionPosition_189_value = 0;
    gen_01_auditionSlot_188_value = 0;
    gen_01_pendingReorderTo_187_value = 0;
    gen_01_pendingReorderFrom_186_value = 0;
    gen_01_pendingReorder_185_value = 0;
    gen_01_previousReorderCommit_184_value = 0;
    gen_01_previousAuditionRequest_183_value = 0;
    gen_01_previousRemoveRequest_182_value = 0;
    gen_01_grainStartSchedule_181_value = 0;
    gen_01_previousDelayedGate_180_value = 0;
    gen_01_transportRunSamples_179_value = 0;
    gen_01_timingPhaseReady_178_value = 0;
    gen_01_previousTimingPhase_177_value = 0;
    gen_01_visualStep_176_value = 0;
    gen_01_visualCountdown_175_value = 0;
    gen_01_visualSlot_174_value = 0;
    gen_01_previousClear_173_value = 0;
    gen_01_clearFlushRemaining_172_value = 0;
    gen_01_clearCountdown_171_value = 0;
    gen_01_lastSamplesPerBeat_170_value = 0;
    gen_01_previousHostRunning_169_value = 0;
    gen_01_stealPan_168_value = 0;
    gen_01_stealFadePosition_167_value = 0;
    gen_01_stealInitialGain_166_value = 0;
    gen_01_stealDirection_165_value = 0;
    gen_01_stealPosition_164_value = 0;
    gen_01_stealSlot_163_value = 0;
    gen_01_randomState_162_value = 0;
    gen_01_voiceStart7_161_value = 0;
    gen_01_voiceStart6_160_value = 0;
    gen_01_voiceStart5_159_value = 0;
    gen_01_voiceStart4_158_value = 0;
    gen_01_voiceStart3_157_value = 0;
    gen_01_voiceStart2_156_value = 0;
    gen_01_voiceStart1_155_value = 0;
    gen_01_voiceStart0_154_value = 0;
    gen_01_voicePan7_153_value = 0;
    gen_01_voicePan6_152_value = 0;
    gen_01_voicePan5_151_value = 0;
    gen_01_voicePan4_150_value = 0;
    gen_01_voicePan3_149_value = 0;
    gen_01_voicePan2_148_value = 0;
    gen_01_voicePan1_147_value = 0;
    gen_01_voicePan0_146_value = 0;
    gen_01_voiceReverse7_145_value = 0;
    gen_01_voiceLevel7_144_value = 0;
    gen_01_voiceAttack7_143_value = 0;
    gen_01_voiceBody7_142_value = 0;
    gen_01_voicePos7_141_value = 0;
    gen_01_voiceSlot7_140_value = 0;
    gen_01_voiceReverse6_139_value = 0;
    gen_01_voiceLevel6_138_value = 0;
    gen_01_voiceAttack6_137_value = 0;
    gen_01_voiceBody6_136_value = 0;
    gen_01_voicePos6_135_value = 0;
    gen_01_voiceSlot6_134_value = 0;
    gen_01_voiceReverse5_133_value = 0;
    gen_01_voiceLevel5_132_value = 0;
    gen_01_voiceAttack5_131_value = 0;
    gen_01_voiceBody5_130_value = 0;
    gen_01_voicePos5_129_value = 0;
    gen_01_voiceSlot5_128_value = 0;
    gen_01_voiceReverse4_127_value = 0;
    gen_01_voiceLevel4_126_value = 0;
    gen_01_voiceAttack4_125_value = 0;
    gen_01_voiceBody4_124_value = 0;
    gen_01_voicePos4_123_value = 0;
    gen_01_voiceSlot4_122_value = 0;
    gen_01_voiceReverse3_121_value = 0;
    gen_01_voiceLevel3_120_value = 0;
    gen_01_voiceAttack3_119_value = 0;
    gen_01_voiceBody3_118_value = 0;
    gen_01_voicePos3_117_value = 0;
    gen_01_voiceSlot3_116_value = 0;
    gen_01_voiceReverse2_115_value = 0;
    gen_01_voiceLevel2_114_value = 0;
    gen_01_voiceAttack2_113_value = 0;
    gen_01_voiceBody2_112_value = 0;
    gen_01_voicePos2_111_value = 0;
    gen_01_voiceSlot2_110_value = 0;
    gen_01_voiceReverse1_109_value = 0;
    gen_01_voiceLevel1_108_value = 0;
    gen_01_voiceAttack1_107_value = 0;
    gen_01_voiceBody1_106_value = 0;
    gen_01_voicePos1_105_value = 0;
    gen_01_voiceSlot1_104_value = 0;
    gen_01_voiceReverse0_103_value = 0;
    gen_01_voiceLevel0_102_value = 0;
    gen_01_voiceAttack0_101_value = 0;
    gen_01_voiceBody0_100_value = 0;
    gen_01_voicePos0_99_value = 0;
    gen_01_voiceSlot0_98_value = 0;
    gen_01_nextVoice_97_value = 0;
    gen_01_deferNewest_96_value = 0;
    gen_01_rotationRandomState_95_value = 0;
    gen_01_rotationBeatPhase_94_value = 0;
    gen_01_rotationOffset_93_value = 0;
    gen_01_markovActiveBank_92_value = 0;
    gen_01_previousMarkovCommit_91_value = 0;
    gen_01_previousSelectionMode_90_value = 0;
    gen_01_grainRandomState_89_value = 0;
    gen_01_grainCursor_88_value = 0;
    gen_01_stepIndex_87_value = 0;
    gen_01_clockPhase_86_value = 0;
    gen_01_poolCount_85_value = 0;
    gen_01_captureSlot_84_value = 0;
    gen_01_rearmCounter_83_value = 0;
    gen_01_onsetArmed_82_value = 0;
    gen_01_cooldown_81_value = 0;
    gen_01_adaptiveThreshold_80_value = 0;
    gen_01_activityEnv_79_value = 0;
    gen_01_levelEnv_78_value = 0;
    gen_01_slowEnv_77_value = 0;
    gen_01_fastEnv_76_value = 0;
    gen_01_feedbackR_75__maxdelay = 0;
    gen_01_feedbackR_75_sizemode = 0;
    gen_01_feedbackR_75_wrap = 0;
    gen_01_feedbackR_75_reader = 0;
    gen_01_feedbackR_75_writer = 0;
    gen_01_feedbackL_74__maxdelay = 0;
    gen_01_feedbackL_74_sizemode = 0;
    gen_01_feedbackL_74_wrap = 0;
    gen_01_feedbackL_74_reader = 0;
    gen_01_feedbackL_74_writer = 0;
    gen_01_triggerDelay_73__maxdelay = 0;
    gen_01_triggerDelay_73_sizemode = 0;
    gen_01_triggerDelay_73_wrap = 0;
    gen_01_triggerDelay_73_reader = 0;
    gen_01_triggerDelay_73_writer = 0;
    gen_01_preR_72__maxdelay = 0;
    gen_01_preR_72_sizemode = 0;
    gen_01_preR_72_wrap = 0;
    gen_01_preR_72_reader = 0;
    gen_01_preR_72_writer = 0;
    gen_01_preL_71__maxdelay = 0;
    gen_01_preL_71_sizemode = 0;
    gen_01_preL_71_wrap = 0;
    gen_01_preL_71_reader = 0;
    gen_01_preL_71_writer = 0;
    gen_01_setupDone = false;
    gen_01_param_ScatterloomDSP_sensitivity_lastValue = 0;
    gen_01_param_ScatterloomDSP_autoSensitivity_lastValue = 0;
    gen_01_param_ScatterloomDSP_captureOn_lastValue = 0;
    gen_01_param_ScatterloomDSP_grain_lastValue = 0;
    gen_01_param_ScatterloomDSP_attack_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainCount_lastValue = 0;
    gen_01_param_ScatterloomDSP_steps_lastValue = 0;
    gen_01_param_ScatterloomDSP_pulses_lastValue = 0;
    gen_01_param_ScatterloomDSP_rotation_lastValue = 0;
    gen_01_param_ScatterloomDSP_feedback_lastValue = 0;
    gen_01_param_ScatterloomDSP_mixAmount_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainFeedback_lastValue = 0;
    gen_01_param_ScatterloomDSP_reverseProbability_lastValue = 0;
    gen_01_param_ScatterloomDSP_clearPool_lastValue = 0;
    gen_01_param_ScatterloomDSP_division_lastValue = 0;
    gen_01_param_ScatterloomDSP_rotationInterval_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan0_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan1_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan2_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan3_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan4_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan5_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan6_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan7_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainPan8_lastValue = 0;
    gen_01_param_ScatterloomDSP_grainSelectionMode_lastValue = 0;
    gen_01_param_ScatterloomDSP_loopDivision_lastValue = 0;
    gen_01_param_ScatterloomDSP_timingOffset_lastValue = 0;
    gen_01_param_ScatterloomDSP_removeGrain_lastValue = 0;
    gen_01_param_ScatterloomDSP_auditionGrain_lastValue = 0;
    gen_01_param_ScatterloomDSP_reorderFrom_lastValue = 0;
    gen_01_param_ScatterloomDSP_reorderTo_lastValue = 0;
    gen_01_param_ScatterloomDSP_reorderCommit_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight0_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight1_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight2_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight3_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight4_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight5_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight6_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight7_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovWeight8_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovEditRow_lastValue = 0;
    gen_01_param_ScatterloomDSP_markovCommit_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_bbuBase = 0;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
	static constexpr auto& name0 = "markovMatrixB_70";
	static constexpr auto& file0 = "";
	static constexpr auto& tag0 = "buffer~";
	static constexpr auto& name1 = "markovMatrixA_69";
	static constexpr auto& file1 = "";
	static constexpr auto& tag1 = "buffer~";
	static constexpr auto& name2 = "trimEnds_68";
	static constexpr auto& file2 = "";
	static constexpr auto& tag2 = "buffer~";
	static constexpr auto& name3 = "trimStarts_67";
	static constexpr auto& file3 = "";
	static constexpr auto& tag3 = "buffer~";
	static constexpr auto& name4 = "grainLevels_66";
	static constexpr auto& file4 = "";
	static constexpr auto& tag4 = "buffer~";
	static constexpr auto& name5 = "captureActive_65";
	static constexpr auto& file5 = "";
	static constexpr auto& tag5 = "buffer~";
	static constexpr auto& name6 = "capturePositions_64";
	static constexpr auto& file6 = "";
	static constexpr auto& tag6 = "buffer~";
	static constexpr auto& name7 = "grainQueue_63";
	static constexpr auto& file7 = "";
	static constexpr auto& tag7 = "buffer~";
	static constexpr auto& name8 = "poolR_62";
	static constexpr auto& file8 = "";
	static constexpr auto& tag8 = "buffer~";
	static constexpr auto& name9 = "poolL_61";
	static constexpr auto& file9 = "";
	static constexpr auto& tag9 = "buffer~";
	static constexpr auto& name10 = "gen_01_feedbackR_75_bufferobj";
	static constexpr auto& file10 = "";
	static constexpr auto& tag10 = "buffer~";
	static constexpr auto& name11 = "gen_01_feedbackL_74_bufferobj";
	static constexpr auto& file11 = "";
	static constexpr auto& tag11 = "buffer~";
	static constexpr auto& name12 = "gen_01_triggerDelay_73_bufferobj";
	static constexpr auto& file12 = "";
	static constexpr auto& tag12 = "buffer~";
	static constexpr auto& name13 = "gen_01_preR_72_bufferobj";
	static constexpr auto& file13 = "";
	static constexpr auto& tag13 = "buffer~";
	static constexpr auto& name14 = "gen_01_preL_71_bufferobj";
	static constexpr auto& file14 = "";
	static constexpr auto& tag14 = "buffer~";
	DataRefStrings* operator->() { return this; }
	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number gen_01_in1;
    number gen_01_in2;
    number gen_01_in3;
    number gen_01_in4;
    number gen_01_in5;
    number gen_01_sensitivity;
    number gen_01_autoSensitivity;
    number gen_01_captureOn;
    number gen_01_grain;
    number gen_01_attack;
    number gen_01_grainCount;
    number gen_01_steps;
    number gen_01_pulses;
    number gen_01_rotation;
    number gen_01_feedback;
    number gen_01_mixAmount;
    number gen_01_grainFeedback;
    number gen_01_reverseProbability;
    number gen_01_clearPool;
    number gen_01_division;
    number gen_01_rotationInterval;
    number gen_01_grainPan0;
    number gen_01_grainPan1;
    number gen_01_grainPan2;
    number gen_01_grainPan3;
    number gen_01_grainPan4;
    number gen_01_grainPan5;
    number gen_01_grainPan6;
    number gen_01_grainPan7;
    number gen_01_grainPan8;
    number gen_01_grainSelectionMode;
    number gen_01_loopDivision;
    number gen_01_timingOffset;
    number gen_01_removeGrain;
    number gen_01_auditionGrain;
    number gen_01_reorderFrom;
    number gen_01_reorderTo;
    number gen_01_reorderCommit;
    number gen_01_markovWeight0;
    number gen_01_markovWeight1;
    number gen_01_markovWeight2;
    number gen_01_markovWeight3;
    number gen_01_markovWeight4;
    number gen_01_markovWeight5;
    number gen_01_markovWeight6;
    number gen_01_markovWeight7;
    number gen_01_markovWeight8;
    number gen_01_markovEditRow;
    number gen_01_markovCommit;
    number transport_01_input_number;
    number transport_01_position;
    number transport_01_tempo;
    list transport_01_timesig;
    number transport_01_ticks;
    number beatstosamps_tilde_01_beattime;
    number gen_01_param_ScatterloomDSP_sensitivity_value;
    number gen_01_param_ScatterloomDSP_autoSensitivity_value;
    number gen_01_param_ScatterloomDSP_captureOn_value;
    number gen_01_param_ScatterloomDSP_grain_value;
    number gen_01_param_ScatterloomDSP_attack_value;
    number gen_01_param_ScatterloomDSP_grainCount_value;
    number gen_01_param_ScatterloomDSP_steps_value;
    number gen_01_param_ScatterloomDSP_pulses_value;
    number gen_01_param_ScatterloomDSP_rotation_value;
    number gen_01_param_ScatterloomDSP_feedback_value;
    number gen_01_param_ScatterloomDSP_mixAmount_value;
    number gen_01_param_ScatterloomDSP_grainFeedback_value;
    number gen_01_param_ScatterloomDSP_reverseProbability_value;
    number gen_01_param_ScatterloomDSP_clearPool_value;
    number gen_01_param_ScatterloomDSP_division_value;
    number gen_01_param_ScatterloomDSP_rotationInterval_value;
    number gen_01_param_ScatterloomDSP_grainPan0_value;
    number gen_01_param_ScatterloomDSP_grainPan1_value;
    number gen_01_param_ScatterloomDSP_grainPan2_value;
    number gen_01_param_ScatterloomDSP_grainPan3_value;
    number gen_01_param_ScatterloomDSP_grainPan4_value;
    number gen_01_param_ScatterloomDSP_grainPan5_value;
    number gen_01_param_ScatterloomDSP_grainPan6_value;
    number gen_01_param_ScatterloomDSP_grainPan7_value;
    number gen_01_param_ScatterloomDSP_grainPan8_value;
    number gen_01_param_ScatterloomDSP_grainSelectionMode_value;
    number gen_01_param_ScatterloomDSP_loopDivision_value;
    number gen_01_param_ScatterloomDSP_timingOffset_value;
    number gen_01_param_ScatterloomDSP_removeGrain_value;
    number gen_01_param_ScatterloomDSP_auditionGrain_value;
    number gen_01_param_ScatterloomDSP_reorderFrom_value;
    number gen_01_param_ScatterloomDSP_reorderTo_value;
    number gen_01_param_ScatterloomDSP_reorderCommit_value;
    number gen_01_param_ScatterloomDSP_markovWeight0_value;
    number gen_01_param_ScatterloomDSP_markovWeight1_value;
    number gen_01_param_ScatterloomDSP_markovWeight2_value;
    number gen_01_param_ScatterloomDSP_markovWeight3_value;
    number gen_01_param_ScatterloomDSP_markovWeight4_value;
    number gen_01_param_ScatterloomDSP_markovWeight5_value;
    number gen_01_param_ScatterloomDSP_markovWeight6_value;
    number gen_01_param_ScatterloomDSP_markovWeight7_value;
    number gen_01_param_ScatterloomDSP_markovWeight8_value;
    number gen_01_param_ScatterloomDSP_markovEditRow_value;
    number gen_01_param_ScatterloomDSP_markovCommit_value;
    number scatterloomEffectiveRotation = 0;
    number scatterloomEffectiveSensitivity = 0;
    number scatterloomPoolCount = 0;
    number scatterloomClearActive = 0;
    number scatterloomCurrentStep = 0;
    number scatterloomTransportRunning = 0;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[1];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number gen_01_slide_198_prev;
    number gen_01_slide_200_prev;
    number gen_01_slide_202_prev;
    number gen_01_slide_204_prev;
    number gen_01_slide_206_prev;
    number gen_01_slide_208_prev;
    number gen_01_slide_210_prev;
    number gen_01_slide_212_prev;
    number gen_01_feedbackAge_197_value;
    number gen_01_loopDelayFade_196_value;
    number gen_01_previousLoopDelaySamples_195_value;
    number gen_01_loopDelaySamples_194_value;
    number gen_01_auditionStart_193_value;
    number gen_01_auditionLevel_192_value;
    number gen_01_auditionAttack_191_value;
    number gen_01_auditionBody_190_value;
    number gen_01_auditionPosition_189_value;
    number gen_01_auditionSlot_188_value;
    number gen_01_pendingReorderTo_187_value;
    number gen_01_pendingReorderFrom_186_value;
    number gen_01_pendingReorder_185_value;
    number gen_01_previousReorderCommit_184_value;
    number gen_01_previousAuditionRequest_183_value;
    number gen_01_previousRemoveRequest_182_value;
    number gen_01_grainStartSchedule_181_value;
    number gen_01_previousDelayedGate_180_value;
    number gen_01_transportRunSamples_179_value;
    number gen_01_timingPhaseReady_178_value;
    number gen_01_previousTimingPhase_177_value;
    number gen_01_visualStep_176_value;
    number gen_01_visualCountdown_175_value;
    number gen_01_visualSlot_174_value;
    number gen_01_previousClear_173_value;
    number gen_01_clearFlushRemaining_172_value;
    number gen_01_clearCountdown_171_value;
    number gen_01_lastSamplesPerBeat_170_value;
    number gen_01_previousHostRunning_169_value;
    number gen_01_stealPan_168_value;
    number gen_01_stealFadePosition_167_value;
    number gen_01_stealInitialGain_166_value;
    number gen_01_stealDirection_165_value;
    number gen_01_stealPosition_164_value;
    number gen_01_stealSlot_163_value;
    number gen_01_randomState_162_value;
    number gen_01_voiceStart7_161_value;
    number gen_01_voiceStart6_160_value;
    number gen_01_voiceStart5_159_value;
    number gen_01_voiceStart4_158_value;
    number gen_01_voiceStart3_157_value;
    number gen_01_voiceStart2_156_value;
    number gen_01_voiceStart1_155_value;
    number gen_01_voiceStart0_154_value;
    number gen_01_voicePan7_153_value;
    number gen_01_voicePan6_152_value;
    number gen_01_voicePan5_151_value;
    number gen_01_voicePan4_150_value;
    number gen_01_voicePan3_149_value;
    number gen_01_voicePan2_148_value;
    number gen_01_voicePan1_147_value;
    number gen_01_voicePan0_146_value;
    number gen_01_voiceReverse7_145_value;
    number gen_01_voiceLevel7_144_value;
    number gen_01_voiceAttack7_143_value;
    number gen_01_voiceBody7_142_value;
    number gen_01_voicePos7_141_value;
    number gen_01_voiceSlot7_140_value;
    number gen_01_voiceReverse6_139_value;
    number gen_01_voiceLevel6_138_value;
    number gen_01_voiceAttack6_137_value;
    number gen_01_voiceBody6_136_value;
    number gen_01_voicePos6_135_value;
    number gen_01_voiceSlot6_134_value;
    number gen_01_voiceReverse5_133_value;
    number gen_01_voiceLevel5_132_value;
    number gen_01_voiceAttack5_131_value;
    number gen_01_voiceBody5_130_value;
    number gen_01_voicePos5_129_value;
    number gen_01_voiceSlot5_128_value;
    number gen_01_voiceReverse4_127_value;
    number gen_01_voiceLevel4_126_value;
    number gen_01_voiceAttack4_125_value;
    number gen_01_voiceBody4_124_value;
    number gen_01_voicePos4_123_value;
    number gen_01_voiceSlot4_122_value;
    number gen_01_voiceReverse3_121_value;
    number gen_01_voiceLevel3_120_value;
    number gen_01_voiceAttack3_119_value;
    number gen_01_voiceBody3_118_value;
    number gen_01_voicePos3_117_value;
    number gen_01_voiceSlot3_116_value;
    number gen_01_voiceReverse2_115_value;
    number gen_01_voiceLevel2_114_value;
    number gen_01_voiceAttack2_113_value;
    number gen_01_voiceBody2_112_value;
    number gen_01_voicePos2_111_value;
    number gen_01_voiceSlot2_110_value;
    number gen_01_voiceReverse1_109_value;
    number gen_01_voiceLevel1_108_value;
    number gen_01_voiceAttack1_107_value;
    number gen_01_voiceBody1_106_value;
    number gen_01_voicePos1_105_value;
    number gen_01_voiceSlot1_104_value;
    number gen_01_voiceReverse0_103_value;
    number gen_01_voiceLevel0_102_value;
    number gen_01_voiceAttack0_101_value;
    number gen_01_voiceBody0_100_value;
    number gen_01_voicePos0_99_value;
    number gen_01_voiceSlot0_98_value;
    number gen_01_nextVoice_97_value;
    number gen_01_deferNewest_96_value;
    number gen_01_rotationRandomState_95_value;
    number gen_01_rotationBeatPhase_94_value;
    number gen_01_rotationOffset_93_value;
    number gen_01_markovActiveBank_92_value;
    number gen_01_previousMarkovCommit_91_value;
    number gen_01_previousSelectionMode_90_value;
    number gen_01_grainRandomState_89_value;
    number gen_01_grainCursor_88_value;
    number gen_01_stepIndex_87_value;
    number gen_01_clockPhase_86_value;
    number gen_01_poolCount_85_value;
    number gen_01_captureSlot_84_value;
    number gen_01_rearmCounter_83_value;
    number gen_01_onsetArmed_82_value;
    number gen_01_cooldown_81_value;
    number gen_01_adaptiveThreshold_80_value;
    number gen_01_activityEnv_79_value;
    number gen_01_levelEnv_78_value;
    number gen_01_slowEnv_77_value;
    number gen_01_fastEnv_76_value;
    Float64BufferRef gen_01_feedbackR_75_buffer;
    Index gen_01_feedbackR_75__maxdelay;
    Int gen_01_feedbackR_75_sizemode;
    Index gen_01_feedbackR_75_wrap;
    Int gen_01_feedbackR_75_reader;
    Int gen_01_feedbackR_75_writer;
    Float64BufferRef gen_01_feedbackL_74_buffer;
    Index gen_01_feedbackL_74__maxdelay;
    Int gen_01_feedbackL_74_sizemode;
    Index gen_01_feedbackL_74_wrap;
    Int gen_01_feedbackL_74_reader;
    Int gen_01_feedbackL_74_writer;
    Float64BufferRef gen_01_triggerDelay_73_buffer;
    Index gen_01_triggerDelay_73__maxdelay;
    Int gen_01_triggerDelay_73_sizemode;
    Index gen_01_triggerDelay_73_wrap;
    Int gen_01_triggerDelay_73_reader;
    Int gen_01_triggerDelay_73_writer;
    Float64BufferRef gen_01_preR_72_buffer;
    Index gen_01_preR_72__maxdelay;
    Int gen_01_preR_72_sizemode;
    Index gen_01_preR_72_wrap;
    Int gen_01_preR_72_reader;
    Int gen_01_preR_72_writer;
    Float64BufferRef gen_01_preL_71_buffer;
    Index gen_01_preL_71__maxdelay;
    Int gen_01_preL_71_sizemode;
    Index gen_01_preL_71_wrap;
    Int gen_01_preL_71_reader;
    Int gen_01_preL_71_writer;
    SampleBufferRef gen_01_markovMatrixB_70;
    SampleBufferRef gen_01_markovMatrixA_69;
    SampleBufferRef gen_01_trimEnds_68;
    SampleBufferRef gen_01_trimStarts_67;
    SampleBufferRef gen_01_grainLevels_66;
    SampleBufferRef gen_01_captureActive_65;
    SampleBufferRef gen_01_capturePositions_64;
    SampleBufferRef gen_01_grainQueue_63;
    SampleBufferRef gen_01_poolR_62;
    SampleBufferRef gen_01_poolL_61;
    bool gen_01_setupDone;
    number gen_01_param_ScatterloomDSP_sensitivity_lastValue;
    number gen_01_param_ScatterloomDSP_autoSensitivity_lastValue;
    number gen_01_param_ScatterloomDSP_captureOn_lastValue;
    number gen_01_param_ScatterloomDSP_grain_lastValue;
    number gen_01_param_ScatterloomDSP_attack_lastValue;
    number gen_01_param_ScatterloomDSP_grainCount_lastValue;
    number gen_01_param_ScatterloomDSP_steps_lastValue;
    number gen_01_param_ScatterloomDSP_pulses_lastValue;
    number gen_01_param_ScatterloomDSP_rotation_lastValue;
    number gen_01_param_ScatterloomDSP_feedback_lastValue;
    number gen_01_param_ScatterloomDSP_mixAmount_lastValue;
    number gen_01_param_ScatterloomDSP_grainFeedback_lastValue;
    number gen_01_param_ScatterloomDSP_reverseProbability_lastValue;
    number gen_01_param_ScatterloomDSP_clearPool_lastValue;
    number gen_01_param_ScatterloomDSP_division_lastValue;
    number gen_01_param_ScatterloomDSP_rotationInterval_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan0_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan1_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan2_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan3_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan4_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan5_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan6_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan7_lastValue;
    number gen_01_param_ScatterloomDSP_grainPan8_lastValue;
    number gen_01_param_ScatterloomDSP_grainSelectionMode_lastValue;
    number gen_01_param_ScatterloomDSP_loopDivision_lastValue;
    number gen_01_param_ScatterloomDSP_timingOffset_lastValue;
    number gen_01_param_ScatterloomDSP_removeGrain_lastValue;
    number gen_01_param_ScatterloomDSP_auditionGrain_lastValue;
    number gen_01_param_ScatterloomDSP_reorderFrom_lastValue;
    number gen_01_param_ScatterloomDSP_reorderTo_lastValue;
    number gen_01_param_ScatterloomDSP_reorderCommit_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight0_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight1_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight2_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight3_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight4_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight5_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight6_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight7_lastValue;
    number gen_01_param_ScatterloomDSP_markovWeight8_lastValue;
    number gen_01_param_ScatterloomDSP_markovEditRow_lastValue;
    number gen_01_param_ScatterloomDSP_markovCommit_lastValue;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    number globaltransport_bbuBase;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef markovMatrixB_70;
    DataRef markovMatrixA_69;
    DataRef trimEnds_68;
    DataRef trimStarts_67;
    DataRef grainLevels_66;
    DataRef captureActive_65;
    DataRef capturePositions_64;
    DataRef grainQueue_63;
    DataRef poolR_62;
    DataRef poolL_61;
    DataRef gen_01_feedbackR_75_bufferobj;
    DataRef gen_01_feedbackL_74_bufferobj;
    DataRef gen_01_triggerDelay_73_bufferobj;
    DataRef gen_01_preR_72_bufferobj;
    DataRef gen_01_preL_71_bufferobj;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    bool _isInitialized = false;
};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

