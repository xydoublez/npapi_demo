using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using System.Reflection;

namespace DotNetActiveX
{
    /// <summary>
    /// COM Interface - enables to run c# code from c++
    /// </summary>
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface ICSSExplorerInterface
    {
        void setButtonCaption(String strNewCaption);
        void setAdapterDllPtr(IntPtr i_AdapterDllPtr);
    }

    [ProgId("DotNetActiveX.MyDotNetActiveX")]
    [ClassInterface(ClassInterfaceType.None)]
    public partial class MyDotNetActiveX : UserControl, ICSSExplorerInterface
    {
        private static uint DOT_NET_BUTTON_PRESSED = 0x0400;

        private IntPtr m_AdapterDllPtr;                            // ptr to dll adapter

        public MyDotNetActiveX()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Set new caption for Button OK
        /// </summary>
        /// <param name="strNewCaption">New Caption String</param>
        public void setButtonCaption(String strNewCaption)
        {
            btnOK.Text = strNewCaption;
        }

        /// <summary>
        /// This function updates via c++ code, and set the handle to our adapter
        /// </summary>
        /// <param name="i_AdapterDllPtr">pointer to adapter written in c++</param>
        public void setAdapterDllPtr(IntPtr i_AdapterDllPtr)
        {
            m_AdapterDllPtr = i_AdapterDllPtr;
        }   
        
        /// <summary>
        /// Regsiter ActiveX dll function
        /// </summary>
        /// <param name="i_Key">registration key</param>
        [ComRegisterFunction()]
        public static void RegisterClass(string i_Key)
        {
            // strip off HKEY_CLASSES_ROOT\ from the passed key as I don't need it
            StringBuilder sb = new StringBuilder(i_Key);
            sb.Replace(@"HKEY_CLASSES_ROOT\", "");

            // open the CLSID\{guid} key for write access
            RegistryKey registerKey = Registry.ClassesRoot.OpenSubKey(sb.ToString(), true);

            // and create the 'Control' key - this allows it to show up in 
            // the ActiveX control container 
            RegistryKey ctrl = registerKey.CreateSubKey("Control");
            ctrl.Close();

            // next create the CodeBase entry - needed if not string named and GACced.
            RegistryKey inprocServer32 = registerKey.OpenSubKey("InprocServer32", true);
            inprocServer32.SetValue("CodeBase", Assembly.GetExecutingAssembly().CodeBase);
            inprocServer32.Close();

            // finally close the main key
            registerKey.Close();
        }

        /// <summary>
        /// Unregister ActiveX dll function
        /// </summary>
        /// <param name="i_Key"></param>
        [ComUnregisterFunction()]
        public static void UnregisterClass(string i_Key)
        {
            // strip off HKEY_CLASSES_ROOT\ from the passed key as I don't need it
            StringBuilder sb = new StringBuilder(i_Key);
            sb.Replace(@"HKEY_CLASSES_ROOT\", "");

            // open HKCR\CLSID\{guid} for write access
            RegistryKey registerKey = Registry.ClassesRoot.OpenSubKey(sb.ToString(), true);

            // delete the 'Control' key, but don't throw an exception if it does not exist
            registerKey.DeleteSubKey("Control", false);

            // next open up InprocServer32
            RegistryKey inprocServer32 = registerKey.OpenSubKey("InprocServer32", true);

            // and delete the CodeBase key, again not throwing if missing
            inprocServer32.DeleteSubKey("CodeBase", false);

            // finally close the main key
            registerKey.Close();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            SendMessage(m_AdapterDllPtr.ToInt32(), DOT_NET_BUTTON_PRESSED, IntPtr.Zero, IntPtr.Zero);
        }

        #region MAPPING_OF_USER32_DLL_SECTION

        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        public static extern IntPtr SendMessage(
            int hwnd, uint wMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        public static extern int SendMessage(
            int hwnd, uint wMsg, int wParam, string lParam);

        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        public static extern int SendMessage(
            int hwnd, uint wMsg, int wParam, out int lParam);

        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        public static extern int GetNbFiles(
            int hwnd, uint wMsg, int wParam, int lParam);

        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        public static extern int GetFileNames(
            int hwnd, uint wMsg,
            [MarshalAs(UnmanagedType.LPArray)]IntPtr[] wParam,
            int lParam);

        [DllImport("user32.dll", EntryPoint = "SendMessage")]
        public static extern int SendMessage(
            int hwnd, uint wMsg, int wParam, StringBuilder lParam);

        #endregion
    }
}