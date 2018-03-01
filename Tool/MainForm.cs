﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Microsoft.DirectX.PrivateImplementationDetails;


namespace Tool
{
    public partial class MainForm : Form
    {


        public MainForm()
        {
            InitializeComponent();
            InitDevice();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            
        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {
            DeviceForm.Instance.RenderBegin();

            DeviceForm.Instance.RenderEnd();
        }

        private void splitContainer2_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private Device m_Device = null;
        private Sprite m_Sprite = null;

        public void InitDevice()
        {
            PresentParameters presentParams = new PresentParameters();
            SetParameters(presentParams);
            m_Device = new Device(0, DeviceType.Hardware, this
                , CreateFlags.SoftwareVertexProcessing, presentParams);

            m_Sprite = new Sprite(m_Device);
        }

        private void SetParameters(PresentParameters presentParams)
        {
            presentParams.BackBufferWidth = Value.WINCX;
            presentParams.BackBufferHeight = Value.WINCY;
            presentParams.BackBufferFormat = Format.A8B8G8R8;
            presentParams.BackBufferCount = 1;

            presentParams.MultiSample = MultiSampleType.None;
            presentParams.MultiSampleQuality = 0;

            presentParams.SwapEffect = SwapEffect.Discard;
            presentParams.DeviceWindow = this;
            presentParams.Windowed = true;

            presentParams.EnableAutoDepthStencil = true;
            presentParams.AutoDepthStencilFormat = DepthFormat.D24S8;

            presentParams.FullScreenRefreshRateInHz = 0x00000000;
            presentParams.PresentationInterval = PresentInterval.Immediate;
        }

        public void RenderBegin()
        {
            m_Device.Clear(ClearFlags.Target, Color.Blue, 1.0f, 0);
            m_Device.BeginScene();
            m_Sprite.Begin(SpriteFlags.AlphaBlend);
        }

        public void RenderEnd()
        {
            m_Sprite.End();
            m_Device.EndScene();
            m_Device.Present(MainForm.ActiveForm);
        }
    }
}
