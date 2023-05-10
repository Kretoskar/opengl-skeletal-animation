using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HenioEditor.GameProject
{
    class NewProject : ViewModelBase
    {
        private string _name = "NewProject";
        private string _path = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\HenioProject\";

        public string Name
        {
            get => _name;
            set
            {
                if (_name != value)
                {
                    _name = value;
                    OnPropertyChanged(nameof(Name));
                }
            }
        }

        public string Path
        {
            get => _path;
            set
            {
                if (_path != value)
                {
                    _path = value;
                    OnPropertyChanged(nameof(Path));
                }
            }
        }
    }
}
