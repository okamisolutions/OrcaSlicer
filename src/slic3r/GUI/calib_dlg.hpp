#ifndef slic3r_calib_dlg_hpp_
#define slic3r_calib_dlg_hpp_

#include "wxExtensions.hpp"
#include "GUI_Utils.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/RoundedRectangle.hpp"
#include "Widgets/Label.hpp"
#include "Widgets/CheckBox.hpp"
#include "Widgets/ComboBox.hpp"
#include "Widgets/TextInput.hpp"
#include "Widgets/LabeledStaticBox.hpp"
#include "Widgets/RadioGroup.hpp"
#include "GUI_App.hpp"
#include "wx/hyperlink.h"
#include <wx/radiobox.h>
#include "libslic3r/calib.hpp"

namespace Slic3r { namespace GUI {

// ORCA: "Add as an extra test" option of the calibration dialogs. The test joins the ones already on the plate,
// printed by object with the filament picked here, instead of starting a new project.
class CalibExtraTestOption
{
public:
    void create(wxWindow* parent, wxSizer* sizer);
    // Refills the filament list and enables the option when the plate has objects. Done when the dialog is shown.
    void update();
    // Whether the selected kind of test can share the plate (the PA line and pattern cannot).
    void allow(bool allowed);
    // The 1-based filament of the extra test, 0 to start a new project.
    int  filament_id() const;

private:
    void update_enabled();

    CheckBox*        m_checkbox{nullptr};
    wxStaticText*    m_label{nullptr};
    wxStaticText*    m_filament_label{nullptr};
    ComboBox*        m_filament{nullptr};
    std::vector<int> m_filament_ids;
    bool             m_allowed{true};
    bool             m_has_objects{false};
};

class PA_Calibration_Dlg : public DPIDialog
{
public:
    PA_Calibration_Dlg(wxWindow* parent, wxWindowID id, Plater* plater);
    ~PA_Calibration_Dlg();
    void on_dpi_changed(const wxRect& suggested_rect) override;
	void on_show(wxShowEvent& event);
protected:
    void reset_params();
	virtual void on_start(wxCommandEvent& event);
	virtual void on_extruder_type_changed(wxCommandEvent& event);
	virtual void on_method_changed(wxCommandEvent& event);

protected:
	bool m_bDDE;
	Calib_Params m_params;


	RadioGroup* m_rbExtruderType;
	RadioGroup* m_rbMethod;
	TextInput* m_tiStartPA;
	TextInput* m_tiEndPA;
	TextInput* m_tiPAStep;
	CheckBox* m_cbPrintNum;
	TextInput* m_tiBMAccels;
	TextInput* m_tiBMSpeeds;
	CalibExtraTestOption m_extra;

	Plater* m_plater;
};

class Temp_Calibration_Dlg : public DPIDialog
{
public:
    Temp_Calibration_Dlg(wxWindow* parent, wxWindowID id, Plater* plater);
    ~Temp_Calibration_Dlg();
    void on_dpi_changed(const wxRect& suggested_rect) override;

protected:
    
    virtual void on_start(wxCommandEvent& event);
    virtual void on_filament_type_changed(wxCommandEvent& event);
    Calib_Params m_params;

    RadioGroup* m_rbFilamentType;
    TextInput* m_tiStart;
    TextInput* m_tiEnd;
    TextInput* m_tiStep;
    CheckBox*  m_cbResize;
    CalibExtraTestOption m_extra;
    Plater* m_plater;
};

class MaxVolumetricSpeed_Test_Dlg : public DPIDialog
{
public:
    MaxVolumetricSpeed_Test_Dlg(wxWindow* parent, wxWindowID id, Plater* plater);
    ~MaxVolumetricSpeed_Test_Dlg();
    void on_dpi_changed(const wxRect& suggested_rect) override;

protected:

    virtual void on_start(wxCommandEvent& event);
    Calib_Params m_params;

    TextInput* m_tiStart;
    TextInput* m_tiEnd;
    TextInput* m_tiStep;
    Plater* m_plater;
};

class VFA_Test_Dlg : public DPIDialog {
public:
    VFA_Test_Dlg(wxWindow* parent, wxWindowID id, Plater* plater);
    ~VFA_Test_Dlg();
    void on_dpi_changed(const wxRect& suggested_rect) override;

protected:
    virtual void on_start(wxCommandEvent& event);
    Calib_Params m_params;

    TextInput* m_tiStart;
    TextInput* m_tiEnd;
    TextInput* m_tiStep;
    CheckBox*  m_cbAutoAdjust;
    CheckBox*  m_cbResize;
    Plater* m_plater;
};


class Retraction_Test_Dlg : public DPIDialog
{
public:
    Retraction_Test_Dlg (wxWindow* parent, wxWindowID id, Plater* plater);
    ~Retraction_Test_Dlg ();
    void on_dpi_changed(const wxRect& suggested_rect) override;

protected:

    virtual void on_start(wxCommandEvent& event);
    Calib_Params m_params;

    TextInput* m_tiStart;
    TextInput* m_tiEnd;
    TextInput* m_tiStep;
    CalibExtraTestOption m_extra;
    Plater* m_plater;
};

class Input_Shaping_Freq_Test_Dlg : public DPIDialog
{
public:
    Input_Shaping_Freq_Test_Dlg (wxWindow* parent, wxWindowID id, Plater* plater);
    ~Input_Shaping_Freq_Test_Dlg ();
    void on_dpi_changed(const wxRect& suggested_rect) override;
    
protected:

    virtual void on_start(wxCommandEvent& event);
    Calib_Params m_params;

    RadioGroup* m_rbModel;
    RadioGroup* m_rbType;
    TextInput* m_tiFreqStartX;
    TextInput* m_tiFreqEndX;
    TextInput* m_tiFreqStartY;
    TextInput* m_tiFreqEndY;
    TextInput* m_tiDampingFactor;
    Plater* m_plater;
};

class Input_Shaping_Damp_Test_Dlg : public DPIDialog
{
public:
    Input_Shaping_Damp_Test_Dlg (wxWindow* parent, wxWindowID id, Plater* plater);
    ~Input_Shaping_Damp_Test_Dlg ();
    void on_dpi_changed(const wxRect& suggested_rect) override;
    
protected:

    virtual void on_start(wxCommandEvent& event);
    Calib_Params m_params;

    RadioGroup* m_rbModel;
    RadioGroup* m_rbType;
    TextInput* m_tiFreqX;
    TextInput* m_tiFreqY;
    TextInput* m_tiDampingFactorStart;
    TextInput* m_tiDampingFactorEnd;
    Plater* m_plater;
};

class Cornering_Test_Dlg : public DPIDialog
{
public:
    Cornering_Test_Dlg(wxWindow* parent, wxWindowID id, Plater* plater);
    ~Cornering_Test_Dlg();
    void on_dpi_changed(const wxRect& suggested_rect) override;
    
protected:
    virtual void on_start(wxCommandEvent& event);
    Calib_Params m_params;

    RadioGroup* m_rbModel;
    TextInput* m_tiJDStart;
    TextInput* m_tiJDEnd;
    Plater* m_plater;
};

class FlowRateCalibrationDialog : public DPIDialog
{
public:
    FlowRateCalibrationDialog(wxWindow* parent, wxWindowID id, Plater* plater);
    ~FlowRateCalibrationDialog();
    void on_dpi_changed(const wxRect& suggested_rect) override;

protected:
    virtual void on_start(wxCommandEvent& event);

    RadioGroup* m_rbType;
    // ORCA: use standard OrcaSlicer ComboBox instead of BitmapComboBox
    ComboBox* m_rbPattern;
    CalibExtraTestOption m_extra;
    Plater* m_plater;
};
}} // namespace Slic3r::GUI
#endif
