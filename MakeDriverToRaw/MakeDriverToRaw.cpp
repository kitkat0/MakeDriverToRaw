#pragma once
#include <iostream>
#include <fstream>
#include <vector>

void open_binary_file(const std::string& file, std::vector<uint8_t>& data)
{
	std::ifstream fstr(file, std::ios::binary);
	fstr.unsetf(std::ios::skipws);
	fstr.seekg(0, std::ios::end);

	const auto file_size = fstr.tellg();

	fstr.seekg(NULL, std::ios::beg);
	data.reserve(static_cast<uint32_t>(file_size));
	data.insert(data.begin(), std::istream_iterator<uint8_t>(fstr), std::istream_iterator<uint8_t>());
}

int __cdecl main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::perror("[-] The argument is not valid.\n");
		return -1;
	}
	std::vector<std::uint8_t> drv_buffer;
	open_binary_file(argv[1], drv_buffer);
	if (!drv_buffer.size())
	{
		std::perror("[-] invalid drv_buffer size\n");
		return -1;
	}
	printf("std::uint8_t raw_driver[] = { ");
	for (auto buf : drv_buffer) {
		printf("0x%x, ", buf);
	}
	printf("\b\b };");

	system("pause");
}