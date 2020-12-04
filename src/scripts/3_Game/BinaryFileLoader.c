class BinaryFileLoader<Class T>
{
	static bool BinaryLoadFile( string filename, out T data )
	{
		if( FileExist( filename ) )
		{
			FileSerializer serializer = new FileSerializer;
			
			if (!serializer.Open(filename, FileMode.READ)) return false;
			if (!serializer.Read(data)) return false;
			
			serializer.Close();
			return true;
		}
		
		return false;
	}
	
	static bool BinarySaveFile( string filename, T data )
	{
		FileSerializer serializer = new FileSerializer;
			
		if (!serializer.Open(filename, FileMode.WRITE)) return false;		
		if (!serializer.Write(data)) return false;
		
		serializer.Close();
		return true;
	}
}