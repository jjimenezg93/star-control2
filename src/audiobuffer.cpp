#pragma warning(push, 0)
#include "../include/audiobuffer.h"
#include "../include/file.h"
#include "AL\al.h"
#include "AL\alc.h"

#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb_vorbis.c"

AudioBuffer::AudioBuffer(const String &filename) {
	if (filename.ExtractExt() == "wav") {
		m_alBuffer = 0;
		File * file = new File(filename, FILE_READ);

		int32 chunkId = file->ReadInt();
		int32 riffChunkSize = file->ReadInt();
		int32 format = file->ReadInt();
		int32 subChunkId = file->ReadInt();
		int32 fmtChunkSize = file->ReadInt();
		int16 audioFormat = file->ReadInt16();
		int16 channels = file->ReadInt16();
		int32 sampleRate = file->ReadInt();
		int32 byteRate = file->ReadInt();
		int16 blockAlign = file->ReadInt16();
		int16 bitsPerSample = file->ReadInt16();
		if (fmtChunkSize > 16) {
			int16 extraParamsSize = file->ReadInt16();
			file->Seek(file->Pos() + extraParamsSize);
		}

		char text[5] = "";
		file->ReadBytes(text, 4);
		while (String(text) != "data" && !file->Eof()) {
			file->ReadBytes(text, 4);
			if (String(text) == "data")
				break;
			file->Seek(file->Pos() + 4);
		}

		int32 dataSize = file->ReadInt();
		uint32 * data = (uint32 *)malloc(dataSize);
		file->ReadBytes(data, dataSize);

		ALenum bufferFormat;
		if (bitsPerSample == 8) {
			if (channels == 1)
				bufferFormat = AL_FORMAT_MONO8;
			else
				bufferFormat = AL_FORMAT_STEREO8;
		}
		else {
			if (channels == 1)
				bufferFormat = AL_FORMAT_MONO16;
			else
				bufferFormat = AL_FORMAT_STEREO16;
		}

		alGenBuffers(1, &m_alBuffer);
		alBufferData(m_alBuffer, bufferFormat, data, dataSize, sampleRate);
		delete file;
		free(data);
	} else if (filename.ExtractExt() == "ogg") {
		stb_vorbis * file = stb_vorbis_open_filename(filename.ToCString(), nullptr, nullptr);

		if (file) {
			stb_vorbis_info info = stb_vorbis_get_info(file);
			uint32 size = stb_vorbis_stream_length_in_samples(file) * info.channels;
			int16 * buffer = (int16 *)malloc(size * sizeof(int16));
			stb_vorbis_get_samples_short_interleaved(file, info.channels, buffer, size);
			alGenBuffers(1, &m_alBuffer);
			ALenum bufferFormat;
			if (info.channels == 1)
				bufferFormat = AL_FORMAT_MONO16;
			else
				bufferFormat = AL_FORMAT_STEREO16;
			alBufferData(m_alBuffer, bufferFormat, buffer, size, info.sample_rate);
			stb_vorbis_close(file);
			free(buffer);
		}
	}
}

AudioBuffer::~AudioBuffer() {

}

#pragma warning(pop)