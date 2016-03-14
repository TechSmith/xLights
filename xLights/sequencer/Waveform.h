#ifndef WAVEFORM_H
#define WAVEFORM_H

#include "wx/wx.h"

#include "../xlGLCanvas.h"
#include <vector>
#include <string>

#include "../AudioManager.h"

#define VERTICAL_PADDING            10
#define NO_WAVE_VIEW_SELECTED       -1
#define WAVEFORM_SIDE_MARGIN        25
wxDECLARE_EVENT(EVT_WAVE_FORM_MOVED, wxCommandEvent);
wxDECLARE_EVENT(EVT_TIME_SELECTED, wxCommandEvent);
wxDECLARE_EVENT(EVT_SCROLL_RIGHT, wxCommandEvent);
wxDECLARE_EVENT(EVT_ZOOM, wxCommandEvent);
wxDECLARE_EVENT(EVT_MOUSE_POSITION, wxCommandEvent);

class TimeLine;

enum DRAG_MODE {
    DRAG_NORMAL,
    DRAG_LEFT_EDGE,
    DRAG_RIGHT_EDGE
};

class Waveform : public xlGLCanvas
{
    public:
		int OpenfileMedia(AudioManager* media, wxString& error);
		void CloseMedia();

        void SetZoomLevel(int level);
        int GetZoomLevel();

        int SetStartPixelOffset(int startPixel);
        int GetStartPixelOffset();

        void SetTimeFrequency(int frequency);
        int GetTimeFrequency();

        void SetTimeline(TimeLine* timeLine);

        void UpdatePlayMarker();
        void CheckNeedToScroll();

        Waveform(wxPanel* parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition,
                const wxSize &size=wxDefaultSize,long style=0, const wxString &name=wxPanelNameStr);
		virtual ~Waveform();

        struct MINMAX
        {
            float min;
            float max;
        };

    protected:
		virtual void InitializeGLCanvas();

    private:
      	DECLARE_EVENT_TABLE()
        void GetMinMaxSampleSet(int setSize, float*sampleData,int trackSize, MINMAX* minMax);
        float GetSamplesPerLineFromZoomLevel(int ZoomLevel);
		TimeLine* mTimeline;
        wxPanel* mParent;
        wxWindow* mMainWindow;
        int mStartPixelOffset;
        int mCurrentWaveView;
        int mMediaTrackSize;
        int mFrequency;
        int mZoomLevel;
        bool mPointSize;
        bool m_dragging;
        DRAG_MODE m_drag_mode;
		AudioManager* _media;

        class WaveView
        {
            private:
            float mSamplesPerPixel;
            int mZoomLevel;

            public:

            std::vector<MINMAX> MinMaxs;
            WaveView(int ZoomLevel,float SamplesPerPixel, AudioManager* media)
            {
                mZoomLevel = ZoomLevel;
                mSamplesPerPixel = SamplesPerPixel;
                SetMinMaxSampleSet(SamplesPerPixel, media);
            }


            WaveView(int ZoomLevel)
            {

            }

            virtual ~WaveView()
            {
            }

            int GetZoomLevel()
            {
                return  mZoomLevel;
            }

            void SetMinMaxSampleSet(float SamplesPerPixel, AudioManager* media);

        };

        void DrawWaveView(const WaveView &wv);
        void StartDrawing(wxDouble pointSize);
        void renderGL( wxPaintEvent& event );
        void renderGL();
        void UpdateMousePosition(int time);
      	void mouseMoved(wxMouseEvent& event);
        void mouseWheelMoved(wxMouseEvent& event);
      	void mouseLeftDown(wxMouseEvent& event);
      	void mouseLeftUp( wxMouseEvent& event);
      	void OnLeftDClick(wxMouseEvent& event);
        void OnLostMouseCapture(wxMouseCaptureLostEvent& event);
        void mouseLeftWindow(wxMouseEvent& event);
        void OutputText(GLfloat x, GLfloat y, char *text);
        void drawString (void * font, char *s, float x, float y, float z);
        std::vector<WaveView> views;


};

#endif // WAVEFORM_H
