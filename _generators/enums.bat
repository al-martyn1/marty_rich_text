@umba-enum-gen --help > umba-enum-gen-help.txt

@set FLAGS_ENUM=--enum-flags=0  --enum-flags=enum-class,type-decl
@set FLAGS_FLAGS=--enum-flags=0 --enum-flags=flags,enum-class,type-decl
@set FLAGS_SERIALIZE=--enum-flags=serialize,deserialize,lowercase
@set FLAGS_SERIALIZE_PLUS=--enum-flags=serialize,deserialize,lowercase,extra,serializeSet,deserializeSet

@set UINT32=--underlaying-type=std::uint32_t


@umba-enum-gen @enums.rsp ^
%FLAGS_FLAGS% %UINT32% %FLAGS_SERIALIZE_PLUS%  -E=BasicStyleFlags         -F=@BasicStyleFlags.txt  ^
%FLAGS_ENUM%  %UINT32%                         -E=VariantValueType        -F=@VariantValueType.txt ^
%FLAGS_ENUM%  %UINT32%                         -E=ParaType                -F=@ParaType.txt ^
%FLAGS_ENUM%  %UINT32%                         -E=BlockType               -F=@BlockType.txt ^
%FLAGS_ENUM%  %UINT32% %FLAGS_SERIALIZE%       -E=Align                   -F=@Align.txt ^
%FLAGS_ENUM%  %UINT32% %FLAGS_SERIALIZE%       -E=VertAlign               -F=@VertAlign.txt ^
%FLAGS_ENUM%  %UINT32% %FLAGS_SERIALIZE%       -E=TdThType                -F=@TdThType.txt ^
..\Enums.h

rem %FLAGS_ENUM%  %UINT32%                         -E=EpigraphPoemCiteType    -F=@EpigraphPoemCiteType.txt 
