using Dangl.AVA.Contents.ServiceSpecificationContents;
using System.IO;
using System.Linq;

namespace Dangl.AVA.Interop
{
    public static class AvaConverter
    {
        public static Project ConvertGaebToAva(string gaebFilePath)
        {
            using (var fs = File.OpenRead(gaebFilePath))
            {
                var gaebFile = Dangl.GAEB.Reader.GAEBReader.ReadGaeb(fs);
                var avaProject = Dangl.AVA.Converter.Converter.ConvertFromGaeb(gaebFile);
                return avaProject;
            }
        }

        public static Position[] GetPositionsInProject(Project avaProject)
        {
            return avaProject.ServiceSpecifications
                .First()
                .RecursiveElements()
                .OfType<Position>()
                .ToArray();
        }

        public static void ExportToGaeb(Project avaProject, string gaebFilePath, GaebTargetType gaebTargetType)
        {
            var gaebFile = Dangl.AVA.Converter.Converter.ConvertToGaeb(avaProject, destinationType: gaebTargetType.ToDestinationType());
            using (var fs = File.Create(gaebFilePath))
            {
                using (var gaebStream = Dangl.GAEB.Writer.GAEBWriter.GetStream(gaebFile))
                {
                    gaebStream.CopyTo(fs);
                }
            }
        }

        private static AVA.Converter.DestinationGAEBType ToDestinationType(this GaebTargetType gaebTargetType)
        {
            switch (gaebTargetType)
            {
                case GaebTargetType.Gaeb90:
                    return AVA.Converter.DestinationGAEBType.GAEB90;

                case GaebTargetType.Gaeb2000:
                    return AVA.Converter.DestinationGAEBType.GAEB2000;

                default:
                    return AVA.Converter.DestinationGAEBType.GAEBXML_V3_2;
            }
        }
    }
}
