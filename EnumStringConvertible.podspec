Pod::Spec.new do |s|
  s.name         = "EnumStringConvertible"
  s.version      = "1.0.0"
  s.summary      = "Macro of Convert Enum to NSString in Objective-c."
  s.homepage     = "http://pinchsun.com"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { 'Pinch sun' => 'me@pinchsun.com' }
  s.source       = { :git => "https://github.com/PINKONG/EnumStringConvertible.git", :tag => s.version.to_s }
  s.source_files = '*.{h,m}'
end
